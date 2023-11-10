import { ModelJob } from './../model/ModelJob';
class DataMonth{
    curDate:Date;
    jobArr:ModelJob[];
    dateArr:{year:number,month:number,day:number,isCurMonth:boolean,isCurDay:boolean}[] = [];
    private async initJobArr(){
        let startDate = this.dateArr[0];
        let endDate = this.dateArr[this.dateArr.length-1];
        let start = new Date(startDate.year,startDate.month-1,startDate.day,0,0,0,0).getTime();
        let end = new Date(endDate.year,endDate.month-1,endDate.day,23,59,59,999).getTime();
        let {ipcRenderer} = require("electron")
        this.jobArr = await ipcRenderer.invoke("getData","SELECT * FROM Job WHERE StartTime >= ? and EndTime <= ? order by StartTime asc",start,end)
    }
    private initDateArr(tarDate:Date){
        let year = tarDate.getFullYear();
        let month = tarDate.getMonth();
        let date = tarDate.getDate();
        let preMonthLastDay = new Date(year,month,0);
        let weekIndex = preMonthLastDay.getDay();
        weekIndex = weekIndex===0?7:weekIndex;
        for(let i=preMonthLastDay.getDate() - weekIndex+1;i<=preMonthLastDay.getDate();i++){
            this.dateArr.push({
                year:preMonthLastDay.getFullYear(),
                month:preMonthLastDay.getMonth()+1,
                day:i,
                isCurMonth:false,
                isCurDay:false,
            })
        }
        let curMonthLastDay = new Date(year,month+1,0);
        for(let i=1;i<=curMonthLastDay.getDate();i++){
            this.dateArr.push({
                year:curMonthLastDay.getFullYear(),
                month:curMonthLastDay.getMonth()+1,
                day:i,
                isCurMonth:true,
                isCurDay:i === date,
            })
        }    
        let lastDayCount = 42 - this.dateArr.length;
        if(lastDayCount > 0){
            let nextMonthLastDay = new Date(year,month+2,0);
            for(let i=1;i<=lastDayCount;i++){
                this.dateArr.push({
                    year:nextMonthLastDay.getFullYear(),
                    month:nextMonthLastDay.getMonth()+1,
                    day:i,
                    isCurMonth:false,
                    isCurDay:false,
                })
            }
        }
    }
    async init(){        
        this.initDateArr(this.curDate);
        await this.initJobArr()
    }
    constructor(){
        this.curDate = new Date()
    }
}

export let dataMonth = new DataMonth();