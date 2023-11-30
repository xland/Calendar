import Database from "better-sqlite3";
import { app } from "electron";
import fsex from "fs-extra";
import path from "path";
import crypto from "crypto";
import { ModelJob } from "../model/ModelJob";

export class Db {
  db: Database.Database;
  openDb(dbPath: string) {
    try {
      this.db = new Database(dbPath, { timeout: 8000 });
      this.db.pragma("journal_mode = WAL");
    } catch (ex) {
      console.log(ex);
    }
  }
  createDb(dbPath: string) {
    let sql = `CREATE TABLE Job(Id VARCHAR2(36) NOT NULL ON CONFLICT FAIL UNIQUE ON CONFLICT FAIL, CreateTime BIGINT,UpdateTime BIGINT,DeleteTime BIGINT,IsDelete BOOLEAN, 
JobInfo TEXT,RepeatType INT,RepeatTimes INT,RepeatEndDay INT,StartTime BIGINT,EndTime BIGINT,ColorIndex INT);          
CREATE INDEX JobInfo_Index ON Job(JobInfo);
CREATE TABLE Setting(ViewDefault INT DEFAULT 0,LangDefault INT DEFAULT 0,SkinDefault INT DEFAULT 0,AlertBefore INT);
INSERT INTO Setting (ViewDefault,LangDefault,SkinDefault,AlertBefore) VALUES (0,0,0,5);`;
    try {
      this.db = new Database(dbPath, { timeout: 8000 });
      this.db.pragma("journal_mode = WAL");
      this.db.exec(sql);
    } catch (ex) {
      console.log(ex);
    }
  }
  saveToDb(type: string, data: any) {
    if (type === "Job") {
      data = data as ModelJob;
      data.Id = crypto.randomUUID();
      data.CreateTime = Date.now();
      data.UpdateTime = data.CreateTime;
      data.IsDelete = 0;
      let columnNames: string[] = [];
      for (let key in data) {
        columnNames.push(key);
      }
      let insertSql = `INSERT INTO Job (${columnNames.join(",")}) VALUES (@${columnNames.join(",@")})`;
      try {
        let insert = this.db.prepare(insertSql);
        insert.run(data);
      } catch (ex) {
        console.log(ex);
      }
    } else if (type == "") {
    }
  }
  getData(sql: string, ...params) {
    let objs = this.db.prepare(sql).all(params);
    return objs;
  }

  getDataRecent() {
    let count = 12;
    let nowDate = new Date();
    let sql = `SELECT * FROM Job WHERE StartTime >= ${nowDate.getTime()} and RepeatType == 0 order by StartTime asc LIMIT ${count}`;
    let result = this.db.prepare(sql).all() as ModelJob[];
    let repeatJobs = this.db.prepare(`SELECT * FROM Job where RepeatType > 0`).all() as ModelJob[];
    let sortAndRemove = ()=>{
      result.sort((a, b) => a.StartTime - b.StartTime);
      result = result.slice(0, count);
    }
    for (let j = 0; j < repeatJobs.length; j++) {
      let job = repeatJobs[j];
      let start = new Date(job.StartTime);
      if (job.RepeatType === 1) {
        //每天
        start.setFullYear(nowDate.getFullYear());
        start.setMonth(nowDate.getMonth());
        start.setDate(nowDate.getDate());
        let temp = 0;
        while (temp < count) {
          if (start < nowDate) {
            start.setDate(start.getDate() + 1);
          } else {
            job.StartTime = start.getTime();
            let end = new Date(job.EndTime);
            end.setFullYear(start.getFullYear());
            end.setMonth(start.getMonth());
            end.setDate(start.getDate());
            job.EndTime = end.getTime();
            result.push({ ...job });
            start.setDate(start.getDate() + 1);
            temp += 1;
          }
        }
        sortAndRemove();
      } else if (job.RepeatType === 2) {
        //工作日
        start.setFullYear(nowDate.getFullYear());
        start.setMonth(nowDate.getMonth());
        start.setDate(nowDate.getDate());
        let temp = 0;
        while (temp < count) {
          if (start.getDay() === 0 || start.getDay() === 6 || start < nowDate) {
            start.setDate(start.getDate() + 1);
          } else {
            let end = new Date(job.EndTime);
            end.setFullYear(start.getFullYear());
            end.setMonth(start.getMonth());
            end.setDate(start.getDate());
            job.StartTime = start.getTime();
            job.EndTime = end.getTime();
            result.push({ ...job });
            start.setDate(start.getDate() + 1);
            temp += 1;
          }
        }
        sortAndRemove();
      } else if (job.RepeatType === 3) {
        //每周几
        if(start < nowDate){
          let span = nowDate.getTime() - start.getTime()
          let weekCount =  span / (7*24*60*60*1000)
          weekCount = Math.floor(weekCount)
          start.setDate(start.getDate() + 7*weekCount)
        }
        let temp = 0;
        while (temp < count) {
          if (start < nowDate) {
            start.setDate(start.getDate() + 7);
          } else {
            let end = new Date(job.EndTime);
            end.setFullYear(start.getFullYear());
            end.setMonth(start.getMonth());
            end.setDate(start.getDate());
            job.StartTime = start.getTime();
            job.EndTime = end.getTime();
            result.push({ ...job });
            start.setDate(start.getDate() + 7);
            temp += 1;
          }
        }
        sortAndRemove();
      } else if (job.RepeatType === 4) {
        //每月第几天
        start.setFullYear(nowDate.getFullYear());
        start.setMonth(nowDate.getMonth());
        let temp = 0;
        while (temp < count) {
          if (start < nowDate) {
            start.setMonth(start.getMonth() + 1);
          }else{
            let end = new Date(job.EndTime);
            end.setFullYear(start.getFullYear());
            end.setMonth(start.getMonth());
            end.setDate(start.getDate());
            job.StartTime = start.getTime();
            job.EndTime = end.getTime();
            result.push({ ...job });
            start.setMonth(start.getMonth() + 1);
            temp += 1;
          }
        }
        sortAndRemove();
      } else if (job.RepeatType === 5) {
        //每年几月几日
        start.setFullYear(nowDate.getFullYear());
        let temp = 0;
        while (temp < count) {
          if (start < nowDate) {
            start.setFullYear(start.getFullYear() + 1);
          }else{
            let end = new Date(job.EndTime);
            end.setFullYear(start.getFullYear());
            job.StartTime = start.getTime();
            job.EndTime = end.getTime();
            result.push({ ...job });
            start.setFullYear(start.getFullYear() + 1);
            temp += 1;
          }
        }
        sortAndRemove();
      }
    }
    return result;
  }

  getDataOneMonth(startTime: number, endTime: number) {
    let sql = `SELECT * FROM Job WHERE StartTime >= ? and EndTime <= ? and RepeatType == 0 order by StartTime asc`;
    let result = this.db.prepare(sql).all(startTime, endTime) as ModelJob[];
    let repeatJobs = this.db.prepare(`SELECT * FROM Job where RepeatType > 0`).all() as ModelJob[];
    let monthStart = new Date(startTime);
    for (let j = 0; j < repeatJobs.length; j++) {
      let job = repeatJobs[j];
      if (job.RepeatType === 1) {
        //每天
        for (let i = 0; i < 42; i++) {
          let start = new Date(job.StartTime);
          let end = new Date(job.EndTime);
          start.setFullYear(monthStart.getFullYear());
          start.setMonth(monthStart.getMonth());
          start.setDate(monthStart.getDate() + i);

          end.setFullYear(monthStart.getFullYear());
          end.setMonth(monthStart.getMonth());
          end.setDate(monthStart.getDate() + i);
          job.StartTime = start.getTime();
          job.EndTime = end.getTime();
          result.push({ ...job });
        }
      } else if (job.RepeatType === 2) {
        //工作日
        for (let i = 0; i < 42; i++) {
          let arr = [5, 6, 12, 13, 19, 20, 26, 27, 33, 34, 40, 41];
          if (arr.includes(i)) {
            continue;
          }
          let start = new Date(job.StartTime);
          let end = new Date(job.EndTime);
          start.setFullYear(monthStart.getFullYear());
          start.setMonth(monthStart.getMonth());
          start.setDate(monthStart.getDate() + i);
          end.setFullYear(monthStart.getFullYear());
          end.setMonth(monthStart.getMonth());
          end.setDate(monthStart.getDate() + i);
          job.StartTime = start.getTime();
          job.EndTime = end.getTime();
          result.push({ ...job });
        }
      } else if (job.RepeatType === 3) {
        //每周几
        for (let i = 0; i < 6; i++) {
          let start = new Date(job.StartTime);
          let end = new Date(job.EndTime);
          let num = start.getDay() === 0 ? 6 : start.getDay() - 1;
          start.setFullYear(monthStart.getFullYear());
          start.setMonth(monthStart.getMonth());
          start.setDate(monthStart.getDate() + num + i * 7);
          end.setFullYear(monthStart.getFullYear());
          end.setMonth(monthStart.getMonth());
          end.setDate(monthStart.getDate() + num + i * 7);
          job.StartTime = start.getTime();
          job.EndTime = end.getTime();
          result.push({ ...job });
        }
      } else if (job.RepeatType === 4) {
        //每月第几天
        let start = new Date(job.StartTime);
        start.setFullYear(monthStart.getFullYear());
        start.setMonth(monthStart.getMonth());

        if (start.getTime() < endTime && start.getTime() > startTime) {
          let end = new Date(job.EndTime);
          end.setFullYear(monthStart.getFullYear());
          end.setMonth(monthStart.getMonth());
          job.StartTime = start.getTime();
          job.EndTime = end.getTime();
          result.push({ ...job });
        }
        start.setMonth(start.getMonth() + 1);
        if (start.getTime() < endTime && start.getTime() > startTime) {
          let end = new Date(job.EndTime);
          end.setFullYear(start.getFullYear());
          end.setMonth(start.getMonth());
          job.StartTime = start.getTime();
          job.EndTime = end.getTime();
          result.push({ ...job });
        }
      } else if (job.RepeatType === 5) {
        //每年几月几日
        let start = new Date(job.StartTime);
        start.setFullYear(monthStart.getFullYear());
        if (start.getMonth() === monthStart.getMonth()) {
          if (start.getTime() > monthStart.getTime()) {
            let end = new Date(job.EndTime);
            end.setFullYear(start.getFullYear());
            job.StartTime = start.getTime();
            job.EndTime = end.getTime();
            result.push({ ...job });
          }
        } else if (start.getMonth() === monthStart.getMonth() + 1) {
          let end = new Date(job.EndTime);
          end.setFullYear(start.getFullYear());
          job.StartTime = start.getTime();
          job.EndTime = end.getTime();
          result.push({ ...job });
        } else if (start.getMonth() === new Date(endTime).getMonth()) {
          if (start.getTime() < endTime) {
            let end = new Date(job.EndTime);
            end.setFullYear(monthStart.getFullYear());
            job.StartTime = start.getTime();
            job.EndTime = end.getTime();
            result.push({ ...job });
          }
        }
      }
    }
    result.sort((a, b) => a.StartTime - b.StartTime);
    return result;
  }
  excuteSQL(sql: string, ...params) {
    try {
      this.db.prepare(sql).run(params);
    } catch (ex) {
      console.log(ex);
    }
  }
  getDataNearby() {
    let repeatJobs = this.getData("SELECT * FROM Job where RepeatType > 0") as ModelJob[];
    let now = Date.now();
    let recentJobs = this.getData(`SELECT * FROM Job where StartTime > ${now}`) as ModelJob[];
    for (let i = 0; i < recentJobs.length; i++) {
      let job = recentJobs[i];
      if (job.RepeatType === 1) {
      }
    }
  }
  init() {
    let dbPath = path.join(app.getPath("userData"), "db");
    let exist = fsex.pathExistsSync(dbPath);
    if (exist) {
      dbPath = path.join(dbPath, "db.db");
      exist = fsex.pathExistsSync(dbPath);
      if (exist) {
        this.openDb(dbPath);
      } else {
        this.createDb(dbPath);
      }
    } else {
      fsex.mkdirSync(dbPath);
      dbPath = path.join(dbPath, "db.db");
      this.createDb(dbPath);
    }
  }
}
