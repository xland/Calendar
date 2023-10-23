import React from "jsx-dom";
import "./SmallCalendar.scss";
export default function () {
    let dateArr:{year:number,month:number,day:number,isCurMonth:boolean,isCurDay:boolean}[] = [];
    let initDateArr = ()=>{
        let curDay = new Date();
        let year = curDay.getFullYear();
        let month = curDay.getMonth();
        let date = curDay.getDate();
        let preMonthLastDay = new Date(year,month,0);
        let weekIndex = preMonthLastDay.getDay();
        weekIndex = weekIndex===0?7:weekIndex;
        for(let i=preMonthLastDay.getDate() - weekIndex+1;i<=preMonthLastDay.getDate();i++){
            dateArr.push({
                year:preMonthLastDay.getFullYear(),
                month:preMonthLastDay.getMonth()+1,
                day:i,
                isCurMonth:false,
                isCurDay:false,
            })
        }
        let curMonthLastDay = new Date(year,month+1,0);
        for(let i=1;i<=curMonthLastDay.getDate();i++){
            dateArr.push({
                year:curMonthLastDay.getFullYear(),
                month:curMonthLastDay.getMonth()+1,
                day:i,
                isCurMonth:true,
                isCurDay:i === date,
            })
        }    
        let lastDayCount = 42 - dateArr.length;
        if(lastDayCount > 0){
            let nextMonthLastDay = new Date(year,month+2,0);
            for(let i=1;i<=lastDayCount;i++){
                dateArr.push({
                    year:nextMonthLastDay.getFullYear(),
                    month:nextMonthLastDay.getMonth()+1,
                    day:i,
                    isCurMonth:false,
                    isCurDay:false,
                })
            }
        }
    }

    let getDateEle = () =>{
        let eles:any[] = [];
        let index = 0;
        for(let i=0;i<6;i++){
            let row = <div class="row"></div>            
            for(let j=0;j<7;j++){
                let cell = <div>{dateArr[index].day}</div>
                if(!dateArr[index].isCurMonth){
                    cell.classList.add("notCurMonth");
                }
                if(dateArr[index].isCurDay){
                    cell.classList.add("selected");
                }
                row.appendChild(cell)
                index += 1;
            }
            eles.push(row);
        }
        return eles;
    }

    initDateArr();


  return <div id="SmallCalendar">
    <div class="row header">
        <div>一</div>
        <div>二</div>
        <div>三</div>
        <div>四</div>
        <div>五</div>
        <div>六</div>
        <div>日</div>
    </div>
    <div>
    { getDateEle() }
    </div>    
  </div>;
}