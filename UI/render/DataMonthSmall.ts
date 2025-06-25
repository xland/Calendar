import { Helper } from "../common/Helper";
import { dataMonth } from "./DataMonth";

class DataMonthSmall {
  curDate: Date;
  dateArr: { year: number; month: number; day: number; isCurMonth: boolean; hasJob: boolean }[] = [];
  async init() {
    this.dateArr = Helper.getOneMonthDate(this.curDate);
    let startDate = this.dateArr[0];
    let endDate = this.dateArr[this.dateArr.length - 1];
    let start = new Date(startDate.year, startDate.month - 1, startDate.day, 0, 0, 0, 0);
    let end = new Date(endDate.year, endDate.month - 1, endDate.day, 23, 59, 59, 999);
    debugger;
    // let { ipcRenderer } = require("electron");
    // let hasJobArr = await ipcRenderer.invoke("hasDataOneMonth", start.getTime(), end.getTime());
    // for (let i = 0; i < 42; i++) {
    //   this.dateArr[i].hasJob = hasJobArr[i];
    // }
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
