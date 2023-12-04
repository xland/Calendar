import { eventer } from "../common/eventer";
import React from "./React";
import "./SmallCalendar.scss";
import { Helper } from "../common/Helper";
import { dataMonthSmall } from "./DataMonthSmall";
import { dataMonth } from "./DataMonth";

export default function () {
  let initDataDom = () => {
    let target = Helper.$id("smallCalendarBox");
    target.innerHTML = "";
    let index = 0;
    for (let i = 0; i < 6; i++) {
      let row = <div class="row"></div>;
      for (let j = 0; j < 7; j++) {
        let dateObj = dataMonthSmall.dateArr[index];
        let cell: HTMLElement = <div class="dayItem">{dateObj.day}</div>;
        if (!dateObj.isCurMonth) {
          cell.classList.add("notCurMonth");
        }
        if (dateObj.year === dataMonth.curDate.getFullYear() && dateObj.month === dataMonth.curDate.getMonth() + 1 && dateObj.day === dataMonth.curDate.getDate()) {
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
      dom.innerHTML = `${dataMonthSmall.curDate.getFullYear()}年${dataMonthSmall.curDate.getMonth() + 1}月`;
    }
  };
  eventer.on("dataReady", async () => {
    initDataDom();
  });
  let goPrevOrNextMonth = async (target: HTMLElement, val: number) => {
    let titleDom = target.parentElement.firstElementChild as HTMLElement;
    let oldMonthIndex = dataMonthSmall.curDate.getMonth();
    dataMonthSmall.curDate.setMonth(oldMonthIndex + val);
    titleDom.innerHTML = `${dataMonthSmall.curDate.getFullYear()}年${dataMonthSmall.curDate.getMonth() + 1}月`;
    dataMonthSmall.dateArr = Helper.getOneMonthDate(dataMonthSmall.curDate);
    await dataMonthSmall.init();
    initDataDom();
  };
  let goPrevMonth = (e: MouseEvent) => {
    let target = e.currentTarget as HTMLElement;
    goPrevOrNextMonth(target, -1);
  };
  let goNextMonth = (e: MouseEvent) => {
    let target = e.currentTarget as HTMLElement;
    goPrevOrNextMonth(target, 1);
  };
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
      dataMonth.curDate = new Date(nowDate.year, nowDate.month - 1, nowDate.day, 0, 0, 0, 0);
      dataMonth.dateArr = Helper.getOneMonthDate(dataMonth.curDate);
      await dataMonth.initJobArr();
    }
    switchLabel.innerHTML = `${nowDate.year}-${nowDate.month}-${nowDate.day}`;
    dispatchEvent(new Event("refreshView"));
    Helper.$id("ViewWeek").style.zIndex = "0";
    Helper.$id("ViewMonth").style.zIndex = "0";
    Helper.$id("ViewDay").style.zIndex = "20";
    let prevTarget = target.parentElement.parentElement.querySelector(".selected");
    prevTarget?.classList.remove("selected");
    target.firstElementChild.classList.add("selected");
    let parent = switchLabel.parentElement;
    let dom = parent.prev();
    dom.children[0].classList.add("selected");
    dom.children[1].classList.remove("selected");
    dom.children[2].classList.remove("selected");
    if (Helper.isCurrentDate(dataMonth.curDate)) {
      parent.nextElementSibling.classList.add("todaySelected");
    } else {
      parent.nextElementSibling.classList.remove("todaySelected");
    }
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
