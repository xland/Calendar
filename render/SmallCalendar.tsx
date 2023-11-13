import { eventer } from "../event/eventer";
import { dataMonth } from "./DataMonth";
import React from "./React";
import "./SmallCalendar.scss";

export default function () {
    eventer.once("dataReady",async ()=>{
      let index = 0;
      let target = document.getElementById("smallCalendarBox");
      for(let i=0;i<6;i++){
          let row = <div class="row"></div>            
          for(let j=0;j<7;j++){
              let cell = <div>{dataMonth.dateArr[index].day}</div>
              if(!dataMonth.dateArr[index].isCurMonth){
                  cell.classList.add("notCurMonth");
              }
              if(dataMonth.dateArr[index].isCurDay){
                  cell.classList.add("selected");
              }
              row.appendChild(cell)
              index += 1;
          }
          target.append(row)
      }
  })
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
    <div id="smallCalendarBox"></div>    
  </div>;
}