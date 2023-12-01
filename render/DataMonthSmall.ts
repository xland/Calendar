import { Helper } from "../common/Helper";
import { dataMonth } from "./DataMonth";

class DataMonthSmall{
    curDate:Date;
    dateArr:{year:number,month:number,day:number,isCurMonth:boolean,isCurDay:boolean,hasJob:boolean}[] = [];
    async init(){     
        this.dateArr = Helper.getOneMonthDate(this.curDate)
    }
    initFirst(){
        this.curDate = dataMonth.curDate
        dataMonth.dateArr.forEach(element => {
            let {year,month,day,isCurMonth,isCurDay} = element;
            this.dateArr.push({
                    year,month,day,isCurMonth,isCurDay,hasJob:element.jobs.length >0
                });
        });
    }
    constructor(){
        
    }
}
export let dataMonthSmall = new DataMonthSmall();