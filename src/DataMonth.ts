import { Helper } from "./common/Helper";
import { ModelJob } from "./model/ModelJob";
class DataMonth {
  curDate: Date;
  dateArr: { year: number; month: number; day: number; isCurMonth: boolean; jobs: ModelJob[] }[];
  idTimerToTomarrow;
  async getDataOneMonth(startTime: number, endTime: number) {
    let sql = `SELECT * FROM Job WHERE StartTime >= ${startTime} and EndTime <= ${endTime} and RepeatType == 0 order by StartTime asc`;
    let result = [] as ModelJob[];
    // data = await horse.db.sql(`SELECT * FROM Job where RepeatType > 0`, "db.db");
    let repeatJobs = [] as ModelJob[];
    let monthStart = new Date(startTime);
    for (let j = 0; j < repeatJobs.length; j++) {
      let job = repeatJobs[j];
      if (job.StartTime > endTime) {
        continue;
      }
      if (job.RepeatType === 1) {
        //每天
        let dayIndex = 0;
        if (job.StartTime > startTime) {
          let span = job.StartTime - startTime;
          dayIndex = Math.floor(span / 86400000); //1天
        }
        let jobStartTime = new Date(job.StartTime);
        let jobEndTime = new Date(job.EndTime);
        let start = new Date(
          monthStart.getFullYear(),
          monthStart.getMonth(),
          monthStart.getDate() + dayIndex,
          jobStartTime.getHours(),
          jobStartTime.getMinutes(),
          jobStartTime.getSeconds(),
          0
        );
        let end = new Date(monthStart.getFullYear(), monthStart.getMonth(), monthStart.getDate() + dayIndex, jobEndTime.getHours(), jobEndTime.getMinutes(), jobEndTime.getSeconds(), 0);
        while (dayIndex < 42) {
          job.StartTime = start.getTime();
          job.EndTime = end.getTime();
          result.push({ ...job });
          start.setDate(start.getDate() + 1);
          end.setDate(end.getDate() + 1);
          dayIndex += 1;
        }
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
          let start = new Date(job.StartTime);
          let end = new Date(job.EndTime);
          start.setFullYear(monthStart.getFullYear());
          start.setMonth(monthStart.getMonth());
          start.setDate(monthStart.getDate() + dayIndex);
          end.setFullYear(monthStart.getFullYear());
          end.setMonth(monthStart.getMonth());
          end.setDate(monthStart.getDate() + dayIndex);
          job.StartTime = start.getTime();
          job.EndTime = end.getTime();
          result.push({ ...job });
          dayIndex += 1;
        }
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
          let start = new Date(job.StartTime);
          let end = new Date(job.EndTime);
          start.setFullYear(monthStart.getFullYear());
          start.setMonth(monthStart.getMonth());
          start.setDate(monthStart.getDate() + dayIndex);
          end.setFullYear(monthStart.getFullYear());
          end.setMonth(monthStart.getMonth());
          end.setDate(monthStart.getDate() + dayIndex);
          job.StartTime = start.getTime();
          job.EndTime = end.getTime();
          result.push({ ...job });
          dayIndex = dayIndex + 7;
        }
      } else if (job.RepeatType === 4) {
        //每月第几天
        let start = new Date(job.StartTime);
        start.setFullYear(monthStart.getFullYear());
        start.setMonth(monthStart.getMonth());
        if (start.getTime() < endTime && start.getTime() > startTime && job.StartTime < start.getTime()) {
          //确保任务创建时间比选中时间早
          let end = new Date(job.EndTime);
          end.setFullYear(monthStart.getFullYear());
          end.setMonth(monthStart.getMonth());
          job.StartTime = start.getTime();
          job.EndTime = end.getTime();
          result.push({ ...job });
        }
        start.setMonth(start.getMonth() + 1);
        if (start.getTime() < endTime && start.getTime() > startTime && job.StartTime < start.getTime()) {
          // 42天里可能右两个选中日
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
  async initJobArr() {
    let startDate = this.dateArr[0];
    let endDate = this.dateArr[this.dateArr.length - 1];
    let start = new Date(startDate.year, startDate.month - 1, startDate.day, 0, 0, 0, 0);
    let end = new Date(endDate.year, endDate.month - 1, endDate.day, 23, 59, 59, 999);
    this.dateArr.forEach((v) => (v.jobs = []));
    let data = await this.getDataOneMonth(start.getTime(), end.getTime());
    for (let i = 0; i < data.length; i++) {
      let jobStartDate = new Date(data[i].StartTime);
      let index = this.dateArr.findIndex((v) => v.year === jobStartDate.getFullYear() && v.month === jobStartDate.getMonth() + 1 && v.day === jobStartDate.getDate());
      if (index < 0) continue;
      this.dateArr[index].jobs.push(data[i]);
    }
  }
  isInCurMonth(dateObj: Date) {
    let startDate = this.dateArr[0];
    let endDate = this.dateArr[this.dateArr.length - 1];
    let start = new Date(startDate.year, startDate.month - 1, startDate.day, 0, 0, 0, 0);
    let end = new Date(endDate.year, endDate.month - 1, endDate.day, 23, 59, 59, 999);
    if (dateObj > start && dateObj < end) {
      return true;
    } else {
      return false;
    }
  }

  getCurWeekFirstDayIndex() {
    let start = new Date(this.curDate.getTime());
    start.setDate(start.getDate() - (start.getDay() - 1));
    let index = this.dateArr.findIndex((v) => v.month === start.getMonth() + 1 && v.day === start.getDate());
    return index;
  }
  getCurDateIndex() {
    let index = this.dateArr.findIndex((v) => v.month === this.curDate.getMonth() + 1 && v.day === this.curDate.getDate());
    return index;
  }
  getJobById(Id: string) {
    for (let i = 0; i < this.dateArr.length; i++) {
      for (let j = 0; j < this.dateArr[i].jobs.length; j++) {
        if (this.dateArr[i].jobs[j].Id === Id) {
          return this.dateArr[i].jobs[j];
        }
      }
    }
  }
  initTimerToTomorrow() {
    let end = new Date(this.curDate.getFullYear(), this.curDate.getMonth(), this.curDate.getDate(), 23, 59, 59, 999);
    let span = end.getTime() - this.curDate.getTime();
    clearTimeout(this.idTimerToTomarrow);
    this.idTimerToTomarrow = setTimeout(() => {
      //todo 第二天，应该更新，原来的逻辑是重启应用
    }, span);
  }
  async init() {
    this.curDate = new Date();
    this.initTimerToTomorrow();
    this.dateArr = Helper.getOneMonthDate(this.curDate);
    await this.initJobArr();
  }
  constructor() {}
}

export let dataMonth = new DataMonth();
