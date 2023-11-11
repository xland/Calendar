import { ModelJob } from './../model/ModelJob';
class DataMonth{
    curDate:Date;
    dateArr:{year:number,month:number,day:number,isCurMonth:boolean,isCurDay:boolean,jobs:ModelJob[]}[] = [];
    private async initJobArr(){
        let startDate = this.dateArr[0];
        let endDate = this.dateArr[this.dateArr.length-1];
        let start = new Date(startDate.year,startDate.month-1,startDate.day,0,0,0,0);
        let end = new Date(endDate.year,endDate.month-1,endDate.day,23,59,59,999);
        let {ipcRenderer} = require("electron")
        let jobArr:ModelJob[] = await ipcRenderer.invoke("getData","SELECT * FROM Job WHERE StartTime >= ? and EndTime <= ? order by StartTime asc",start.getTime(),end.getTime())
        console.log(this.dateArr);
        for(let i=0;i<jobArr.length;i++){
            let jobStartDate = new Date(jobArr[i].StartTime)
            let index = this.dateArr.findIndex(v=>v.month === jobStartDate.getMonth()+1 && v.day === jobStartDate.getDate())
            this.dateArr[index].jobs.push(jobArr[i]);            
        }
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
                jobs:[]
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
                jobs:[]
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
                    jobs:[]
                })
            }
        }
    }
    getCurWeekFirstDayIndex(){
        let start = new Date(this.curDate.getTime());
        start.setDate(start.getDate()-(start.getDay()-1))
        let index = this.dateArr.findIndex(v=>v.month === start.getMonth()+1 && v.day === start.getDate())
        return index;
    }
    async init(){     
        this.curDate = new Date()  
        this.initDateArr(this.curDate);
        await this.initJobArr()
    }
    constructor(){
        
    }
}

export let dataMonth = new DataMonth();