export class Helper{
    static $id(id:string){
        return document.getElementById(id)
    }
    static $select(name:string){
        return document.querySelector(name)
    }
    static isCurrentDate(date:Date){
        let now = new Date();
        return now.getFullYear() === date.getFullYear() && now.getMonth() === date.getMonth() && now.getDate() === date.getDate()
    }
    static getOneMonthDate(tarDate:Date){
        let result = [];
        let year = tarDate.getFullYear();
        let month =tarDate.getMonth();
        let date = tarDate.getDate();
        let preMonthLastDay = new Date(year,month,0);
        let weekIndex = preMonthLastDay.getDay();
        weekIndex = weekIndex===0?7:weekIndex;
        for(let i=preMonthLastDay.getDate() - weekIndex+1;i<=preMonthLastDay.getDate();i++){
            result.push({
                year:preMonthLastDay.getFullYear(),
                month:preMonthLastDay.getMonth()+1,
                day:i,
                isCurMonth:false
            })
        }
        let curMonthLastDay = new Date(year,month+1,0);
        for(let i=1;i<=curMonthLastDay.getDate();i++){
            result.push({
                year:curMonthLastDay.getFullYear(),
                month:curMonthLastDay.getMonth()+1,
                day:i,
                isCurMonth:true
            })
        }    
        let lastDayCount = 42 - result.length;
        if(lastDayCount > 0){
            let nextMonthLastDay = new Date(year,month+2,0);
            for(let i=1;i<=lastDayCount;i++){
                result.push({
                    year:nextMonthLastDay.getFullYear(),
                    month:nextMonthLastDay.getMonth()+1,
                    day:i,
                    isCurMonth:false
                })
            }
        }
        return result;
    }
}