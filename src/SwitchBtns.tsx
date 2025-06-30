import { eventer } from "./common/eventer";
import { dataMonth } from "./DataMonth";
import { dataSetting } from "./DataSetting";
import { Helper } from "./common/Helper";
import { db } from "./common/db";
import React from "./React";
import "./SwitchBtns.scss";
export default function () {
  let switchView = async (name: string, dom: HTMLElement) => {
    let arr = ["ViewDay", "ViewWeek", "ViewMonth"];
    let val = 0;
    for (let i = 0; i < arr.length; i++) {
      if (arr[i] === name) {
        (dom.children[i] as HTMLElement).classList.add("selected");
        Helper.$id(name).style.zIndex = "20";
        val = i;
      } else {
        (dom.children[i] as HTMLElement).classList.add("selected");
        Helper.$id(arr[i]).style.zIndex = "0";
      }
    }
    let sql = `Update Setting set ViewVal = ${val}`;
    db.exec(sql)
  };
  let switchBtnClick = (e) => {
    let target = e.target as HTMLElement;
    if (target.classList.contains("selected")) return;
    let switchLabel = target.parentElement.nextElementSibling.firstElementChild.nextElementSibling;
    if (target.innerHTML === "日") {
      switchLabel.innerHTML = `${dataMonth.curDate.getFullYear()}-${dataMonth.curDate.getMonth() + 1}-${dataMonth.curDate.getDate()}`;
      switchView("ViewDay", target.parentElement);
    }
    if (target.innerHTML === "周") {
      let index = dataMonth.getCurWeekFirstDayIndex();
      switchLabel.innerHTML = `${dataMonth.dateArr[index].month}-${dataMonth.dateArr[index].day}~${dataMonth.dateArr[index + 6].month}-${dataMonth.dateArr[index + 6].day}`;
      switchView("ViewWeek", target.parentElement);
    } else if (target.innerHTML === "月") {
      switchLabel.innerHTML = `${dataMonth.curDate.getFullYear()}年${dataMonth.curDate.getMonth() + 1}月`;
      switchView("ViewMonth", target.parentElement);
    }
  };

  let goToDateView = async (dateObj: Date) => {
    let switchLabel = Helper.$id("switchLabel");
    dataMonth.curDate = dateObj;
    if (!dataMonth.isInCurMonth(dateObj)) {
      dataMonth.dateArr = Helper.getOneMonthDate(dataMonth.curDate);
      await dataMonth.initJobArr();
    }
    switchLabel.innerHTML = `${dateObj.getFullYear()}-${dateObj.getMonth() + 1}-${dateObj.getDate()}`;
    dispatchEvent(new Event("refreshView"));
    let parent = switchLabel.parentElement;
    switchView("ViewDay", parent.previousElementSibling as HTMLElement);
    if (Helper.isCurrentDate(dataMonth.curDate)) {
      parent.nextElementSibling.classList.add("todaySelected");
    } else {
      parent.nextElementSibling.classList.remove("todaySelected");
    }
  };

  let goToDateViewEvent = async (e: CustomEvent) => {
    let dateObj = e.detail as Date;
    goToDateView(dateObj);
  };

  let goPrevOrNext = async (val) => {
    let SwitchBtns = Helper.$id("SwitchBtns");
    let selectedDom = SwitchBtns.querySelector(".selected") as HTMLElement;
    let switchLabel = Helper.$id("switchLabel");
    let oldMonthIndex = dataMonth.curDate.getMonth();
    if (selectedDom.innerHTML === "日") {
      dataMonth.curDate.setDate(dataMonth.curDate.getDate() + val);
      switchLabel.innerHTML = `${dataMonth.curDate.getFullYear()}-${dataMonth.curDate.getMonth() + 1}-${dataMonth.curDate.getDate()}`;
    } else if (selectedDom.innerHTML === "周") {
      dataMonth.curDate.setDate(dataMonth.curDate.getDate() + val * 7);
      let index = dataMonth.getCurWeekFirstDayIndex();
      switchLabel.innerHTML = `${dataMonth.dateArr[index].month}-${dataMonth.dateArr[index].day}~${dataMonth.dateArr[index + 6].month}-${dataMonth.dateArr[index + 6].day}`;
    } else {
      dataMonth.curDate.setMonth(oldMonthIndex + val);
      switchLabel.innerHTML = `${dataMonth.curDate.getFullYear()}年${dataMonth.curDate.getMonth() + 1}月`;
    }
    let nowDate = new Date();
    if (nowDate.getFullYear() === dataMonth.curDate.getFullYear() && nowDate.getMonth() === dataMonth.curDate.getMonth() && nowDate.getDate() === dataMonth.curDate.getDate()) {
      SwitchBtns.lastElementChild.classList.add("todaySelected");
    } else {
      SwitchBtns.lastElementChild.classList.remove("todaySelected");
      if (oldMonthIndex != dataMonth.curDate.getMonth()) {
        dataMonth.dateArr = Helper.getOneMonthDate(dataMonth.curDate);
        await dataMonth.initJobArr();
      }
    }
    dispatchEvent(new Event("refreshView"));
  };

  let prevBtnClick = () => {
    goPrevOrNext(-1);
  };
  let nextBtnClick = () => {
    goPrevOrNext(1);
  };
  let gotoToday = (e: MouseEvent) => {
    let target = e.currentTarget as HTMLElement;
    if (target.classList.contains("todaySelected")) {
      return;
    }
    goToDateView(new Date());
  };
  eventer.once("dataReady", () => {
    let index = dataSetting.setting.ViewDefault;
    if (index === 3) {
      index = dataSetting.setting.ViewVal;
    }
    let dom = Helper.$id("SwitchBtns").firstElementChild;
    switchBtnClick({ target: dom.children[index] });
  });

  return (
    <div id="SwitchBtns" onGoToDateView={goToDateViewEvent}>
      <div class="btns navigateBtns" onClick={switchBtnClick}>
        <div>日</div>
        <div>周</div>
        <div>月</div>
      </div>
      <div class="btns dayBtns">
        <div onClick={prevBtnClick}>
          <i class="iconfont icon-left"></i>
        </div>
        <div id="switchLabel"></div>
        <div onClick={nextBtnClick}>
          <i class="iconfont icon-right"></i>
        </div>
      </div>
      <div onClick={gotoToday} class="btns today todaySelected">
        今
      </div>
    </div>
  );
}
