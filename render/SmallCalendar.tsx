import { eventer } from "../common/eventer";
import React from "./React";
import "./SmallCalendar.scss";
import { Helper } from "../common/Helper";
import { dataMonthSmall } from "./DataMonthSmall";
import { dataMonth } from "./DataMonth";

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
        row.appendChild(
          <div class="dayBox" onClick={cellClick} data-index={index}>
            {cell}
          </div>
        );
        index += 1;
      }
      target.append(row);
      let dom = target.parentElement.firstElementChild.firstElementChild;
      dom.innerHTML = `${dataMonthSmall.curDate.getFullYear() + 1}年${dataMonthSmall.curDate.getMonth()}月`;
    }
  });
  let goPrevMonth = (e: MouseEvent) => {};
  let goNextMonth = (e: MouseEvent) => {};
  let cellClick = async (e: MouseEvent) => {
    let target = e.currentTarget as HTMLElement;
    let index = parseInt(target.dataset.index);
    let switchLabel = Helper.$id("switchLabel");
    let nowDate = dataMonthSmall.dateArr[index];
    if (nowDate.year === dataMonth.curDate.getFullYear() && nowDate.month === dataMonth.curDate.getMonth()) {
      if (nowDate.day === dataMonth.curDate.getDate()) {
        return;
      } else {
        dataMonth.curDate = new Date(nowDate.year, nowDate.month - 1, nowDate.day, 0, 0, 0, 0);
      }
    } else {
      await dataMonth.init();
    }
    switchLabel.parentElement.nextElementSibling.classList.add("todaySelected");
    switchLabel.innerHTML = `${nowDate.year}-${nowDate.month}-${nowDate.day}`;
    dispatchEvent(new Event("refreshView"));
    Helper.$id("ViewWeek").style.zIndex = "0";
    Helper.$id("ViewMonth").style.zIndex = "0";
    Helper.$id("ViewDay").style.zIndex = "20";
    let dom = switchLabel.parentElement.previousElementSibling;
    dom.children[0].classList.add("selected");
    dom.children[1].classList.remove("selected");
    dom.children[2].classList.remove("selected");
    let prevTarget = target.parentElement.parentElement.querySelector(".selected");
    prevTarget.classList.remove("selected");
    target.firstElementChild.classList.add("selected");
  };
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
