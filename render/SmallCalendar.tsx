import { eventer } from "../common/eventer";
import { dataMonth } from "./DataMonth";
import React from "./React";
import "./SmallCalendar.scss";

export default function () {
  let onMouseOver = (e) => {
    let target = e.target as HTMLElement;
    if (target.classList.contains("dayItem")) {
      target = target.parentElement;
    }
    let old = target.parentElement.parentElement.querySelector(".selected") as HTMLElement;
    if (old) {
      old.classList.remove("selected");
    }
    target.firstElementChild.classList.add("selected");
  };
  let mouseLeave = (e: MouseEvent) => {
    let target = document.getElementById("smallCalendarBox").querySelector(".selected") as HTMLElement;
    target.classList.remove("selected");
  };
  eventer.once("dataReady", async () => {
    let index = 0;
    let target = document.getElementById("smallCalendarBox");
    for (let i = 0; i < 6; i++) {
      let row = <div class="row"></div>;
      for (let j = 0; j < 7; j++) {
        let cell = <div class="dayItem">{dataMonth.dateArr[index].day}</div>;
        if (!dataMonth.dateArr[index].isCurMonth) {
          cell.classList.add("notCurMonth");
        }
        if (dataMonth.dateArr[index].isCurDay) {
          cell.classList.add("selected");
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
      <div id="smallCalendarBox" onMouseOver={onMouseOver} onMouseLeave={mouseLeave}></div>
    </div>
  );
}
