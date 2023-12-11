import { eventer } from "../common/eventer";
import { dataMonth } from "./DataMonth";
import { dataSetting } from "./DataSetting";
import { Helper } from "../common/Helper";
import React from "./React";
import "./SwitchBtns.scss";
export default function () {
  let switchView = async (name: string, dom: HTMLElement) => {
    let arr = ["ViewDay", "ViewWeek", "ViewMonth"];
    let val = 0;
    for (let i = 0; i < arr.length; i++) {
      if (arr[i] === name) {
        (dom.children[i] as HTMLElement).classAdd("selected");
        Helper.$id(name).style.zIndex = "20";
        val = i;
      } else {
        (dom.children[i] as HTMLElement).classDel("selected");
        Helper.$id(arr[i]).style.zIndex = "0";
      }
    }
    let sql = `Update Setting set ViewVal = ?`;
    let { ipcRenderer } = require("electron");
    await ipcRenderer.invoke("excuteSQL", sql, val);
  };
  let switchBtnClick = (e) => {
    let target = e.target as HTMLElement;
    if (target.classHas("selected")) return;
    let switchLabel = target.dad().next().son0().next();
    if (target.innerHTML === "日") {
      switchLabel.innerHTML = `${dataMonth.curDate.getFullYear()}-${dataMonth.curDate.getMonth() + 1}-${dataMonth.curDate.getDate()}`;
      switchView("ViewDay", target.dad());
    }
    if (target.innerHTML === "周") {
      let index = dataMonth.getCurWeekFirstDayIndex();
      switchLabel.innerHTML = `${dataMonth.dateArr[index].month}-${dataMonth.dateArr[index].day}~${dataMonth.dateArr[index + 6].month}-${dataMonth.dateArr[index + 6].day}`;
      switchView("ViewWeek", target.dad());
    } else if (target.innerHTML === "月") {
      switchLabel.innerHTML = `${dataMonth.curDate.getFullYear()}年${dataMonth.curDate.getMonth() + 1}月`;
      switchView("ViewMonth", target.dad());
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
    let parent = switchLabel.dad();
    switchView("ViewDay", parent.prev());
    if (Helper.isCurrentDate(dataMonth.curDate)) {
      parent.next().classAdd("todaySelected");
    } else {
      parent.next().classDel("todaySelected");
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
      SwitchBtns.son1().classAdd("todaySelected");
    } else {
      SwitchBtns.son1().classDel("todaySelected");
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
    if (target.classHas("todaySelected")) {
      return;
    }
    goToDateView(new Date());
  };
  eventer.once("dataReady", () => {
    let index = dataSetting.setting.ViewDefault;
    if (index === 3) {
      index = dataSetting.setting.ViewVal;
    }
    let dom = Helper.$id("SwitchBtns").son0();
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
