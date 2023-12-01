import { eventer } from "../common/eventer";
import { dataMonth } from "./DataMonth";
import React from "./React";
import "./SmallCalendar.scss";

export default function () {
  eventer.once("dataReady", async () => {
    let index = 0;
    let target = document.getElementById("smallCalendarBox");
    for (let i = 0; i < 6; i++) {
      let row = <div class="row"></div>;
      for (let j = 0; j < 7; j++) {
        let dateObj = dataMonth.dateArr[index];
        let cell: HTMLElement = <div class="dayItem">{dateObj.day}</div>;
        if (!dateObj.isCurMonth) {
          cell.classList.add("notCurMonth");
        }
        if (dateObj.isCurDay) {
          cell.classList.add("selected");
        }
        if (dateObj.jobs.length > 0) {
          cell.classList.add("hasEvent");
        }
        row.appendChild(<div class="dayBox">{cell}</div>);
        index += 1;
      }
      target.append(row);
    }
  });
  return (
    <div id="SmallCalendar">
      <div class="header">
        <div>一</div>
        <div>二</div>
        <div>三</div>
        <div>四</div>
        <div>五</div>
        <div>六</div>
        <div>日</div>
      </div>
      <div id="smallCalendarBox"></div>
    </div>
  );
}
