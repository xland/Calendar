import { Helper } from "../common/Helper";
import { dataMonth } from "./DataMonth";
import { ModelJob } from "./../model/ModelJob";
class DataMonthSmall {
  curDate: Date;
  dateArr: { year: number; month: number; day: number; isCurMonth: boolean; hasJob: boolean }[] = [];
  async hasDataOneMonth(startTime: number, endTime: number) {
    let hasJob = Array(42).fill(false);

    let data = await horse.db.sql(`SELECT * FROM Job where RepeatType > 0`, "db.db");
    let repeatJobs = data.data as ModelJob[];
    for (let j = 0; j < repeatJobs.length; j++) {
      let job = repeatJobs[j];
      if (job.StartTime > endTime) {
        continue;
      }
      if (job.RepeatType === 1) {
        //每天
        if (job.StartTime < startTime) {
          hasJob.fill(true);
          return hasJob;
        } else {
          let span = job.StartTime - startTime;
          let dayIndex = Math.floor(span / 86400000); //1天
          hasJob.fill(true, dayIndex);
        }
        if (hasJob.findIndex((v) => v === false) < 0) return hasJob;
      } else if (job.RepeatType === 2) {
        //工作日
        let dayIndex = 0;
        if (job.StartTime >= startTime) {
          let span = job.StartTime - startTime;
          dayIndex = Math.floor(span / 86400000); //1天
        }
        let arr = [5, 12, 19, 26, 33, 40];
        while (dayIndex < 42) {
          if (arr.includes(dayIndex)) {
            dayIndex += 2;
            continue;
          }
          hasJob[dayIndex] = true;
          dayIndex += 1;
        }
        if (hasJob.findIndex((v) => v === false) < 0) return hasJob;
      } else if (job.RepeatType === 3) {
        //每周几
        let dayIndex = 0;
        if (job.StartTime > startTime) {
          let span = job.StartTime - startTime;
          dayIndex = Math.floor(span / 86400000); //1天
        } else {
          dayIndex = new Date(job.StartTime).getDay();
          dayIndex = dayIndex === 0 ? 7 : dayIndex;
          dayIndex = dayIndex - 1;
        }
        while (dayIndex < 42) {
          hasJob[dayIndex] = true;
          dayIndex = dayIndex + 7;
        }
        if (hasJob.findIndex((v) => v === false) < 0) return hasJob;
      } else if (job.RepeatType === 4) {
        //每月第几天
        let temp = new Date(startTime);
        let jobDate = new Date(job.StartTime).getDate();
        let i = 0;
        while (i < 42) {
          let step = 1;
          if (temp.getDate() === jobDate) {
            hasJob[i] = true;
            step = 28;
          } else {
            step = 1;
          }
          temp.setDate(temp.getDate() + step);
          i += step;
        }
        if (hasJob.findIndex((v) => v === false) < 0) return hasJob;
      } else if (job.RepeatType === 5) {
        //每年几月几日
        let temp = new Date(startTime);
        let jobDate = new Date(job.StartTime);
        let i = 0;
        while (i < 42) {
          if (temp.getDate() === jobDate.getDate() && temp.getMonth() === jobDate.getMonth()) {
            hasJob[i] = true;
          }
          temp.setDate(temp.getDate() + 1);
          i += 1;
        }
        if (hasJob.findIndex((v) => v === false) < 0) return hasJob;
      }
    }
    let sql = `SELECT * FROM Job WHERE StartTime >= ${startTime} and EndTime <= ${endTime} and RepeatType == 0 order by StartTime asc`;
    data = await horse.db.sql(sql, "db.db");
    let result = data.data as ModelJob[];
    for (let j = 0; j < result.length; j++) {
      let job = result[j];
      let span = job.StartTime - startTime;
      let i = Math.floor(span / 86400000); //1天
      hasJob[i] = true;
    }
    return hasJob;
  }
  async init() {
    this.dateArr = Helper.getOneMonthDate(this.curDate);
    let startDate = this.dateArr[0];
    let endDate = this.dateArr[this.dateArr.length - 1];
    let start = new Date(startDate.year, startDate.month - 1, startDate.day, 0, 0, 0, 0);
    let end = new Date(endDate.year, endDate.month - 1, endDate.day, 23, 59, 59, 999);
    let hasJobArr = await this.hasDataOneMonth(start.getTime(), end.getTime());
    for (let i = 0; i < 42; i++) {
      this.dateArr[i].hasJob = hasJobArr[i];
    }
  }
  initFirst() {
    this.curDate = new Date(dataMonth.curDate.getTime());
    dataMonth.dateArr.forEach((element) => {
      let { year, month, day, isCurMonth } = element;
      this.dateArr.push({
        year,
        month,
        day,
        isCurMonth,
        hasJob: element.jobs.length > 0,
      });
    });
  }
  constructor() {}
}
export let dataMonthSmall = new DataMonthSmall();
