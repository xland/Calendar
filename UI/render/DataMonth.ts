import { Helper } from "../common/Helper";
import { ModelJob } from "./../model/ModelJob";
class DataMonth {
  curDate: Date;
  dateArr: { year: number; month: number; day: number; isCurMonth: boolean; jobs: ModelJob[] }[];
  idTimerToTomarrow;
  async initJobArr() {
    // let startDate = this.dateArr[0];
    // let endDate = this.dateArr[this.dateArr.length - 1];
    // let start = new Date(startDate.year, startDate.month - 1, startDate.day, 0, 0, 0, 0);
    // let end = new Date(endDate.year, endDate.month - 1, endDate.day, 23, 59, 59, 999);
    // this.dateArr.forEach((v) => (v.jobs = []));
    // let { ipcRenderer } = require("electron");
    // let jobArr: ModelJob[] = await ipcRenderer.invoke("getDataOneMonth", start.getTime(), end.getTime());
    // for (let i = 0; i < jobArr.length; i++) {
    //   let jobStartDate = new Date(jobArr[i].StartTime);
    //   let index = this.dateArr.findIndex((v) => v.year === jobStartDate.getFullYear() && v.month === jobStartDate.getMonth() + 1 && v.day === jobStartDate.getDate());
    //     if (index < 0) continue;
    //   this.dateArr[index].jobs.push(jobArr[i]);
    // }
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
    // let end = new Date(this.curDate.getFullYear(), this.curDate.getMonth(), this.curDate.getDate(), 23, 59, 59, 999);
    // let span = end.getTime() - this.curDate.getTime();
    // clearTimeout(this.idTimerToTomarrow);
    // this.idTimerToTomarrow = setTimeout(() => {
    //   let { ipcRenderer } = require("electron");
    //   ipcRenderer.invoke("relaunch");
    // }, span);
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
