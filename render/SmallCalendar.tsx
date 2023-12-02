import { eventer } from "../common/eventer";
import React from "./React";
import "./SmallCalendar.scss";
import { Helper } from "../common/Helper";
import { dataMonthSmall } from "./DataMonthSmall";

export default function () {
  //once("dataReady" todo
  eventer.once("dataReady", async () => {
    let index = 0;
    let target = Helper.$id("smallCalendarBox");
    for (let i = 0; i < 6; i++) {
      let row = <div class="row"></div>;
      for (let j = 0; j < 7; j++) {
        let dateObj = dataMonthSmall.dateArr[index];
        let cell: HTMLElement = <div class="dayItem">{dateObj.day}</div>;
        if (!dateObj.isCurMonth) {
          cell.classList.add("notCurMonth");
        }
        if (dateObj.isCurDay) {
          cell.classList.add("selected");
        }
        if (dateObj.hasJob) {
          cell.classList.add("hasEvent");
        }
        row.appendChild(<div class="dayBox">{cell}</div>);
        index += 1;
      }
      target.append(row);
      let dom = target.parentElement.firstElementChild.firstElementChild;
      dom.innerHTML = `${dataMonthSmall.curDate.getFullYear() + 1}年${dataMonthSmall.curDate.getMonth()}月`;
    }
  });
  let goPrevMonth = (e: MouseEvent) => {};
  let goNextMonth = (e: MouseEvent) => {};
  return (
    <div id="SmallCalendar">
      <div class="titlebar">
        <div class="title"></div>
        <div onClick={goPrevMonth} class="btn">
          <i class="iconfont icon-zuojiantou"></i>
        </div>
        <div onClick={goNextMonth} class="btn">
          <i class="iconfont icon-youjiantou"></i>
        </div>
      </div>
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
