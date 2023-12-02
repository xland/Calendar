import { eventer } from "../common/eventer";
import { dataMonth } from "./DataMonth";
import { dataSetting } from "./DataSetting";
import { Helper } from "../common/Helper";
import React from "./React";
import "./SwitchBtns.scss";
export default function () {
  let switchBtnClick = (e) => {
    let target = e.target as HTMLElement;
    if (target.classList.contains("selected")) return;
    let selectedDom = target.parentElement.querySelector(".selected") as HTMLElement;
    if (selectedDom) {
      selectedDom.classList.remove("selected");
    }
    let arr = ["ViewDay", "ViewWeek", "ViewMonth"];
    arr.forEach((v) => {
      Helper.$id(v).style.zIndex = "0";
    });
    target.classList.add("selected");
    let switchLabel = Helper.$id("switchLabel");
    let index = 0;
    if (target.innerHTML === "日") {
      switchLabel.innerHTML = `${dataMonth.curDate.getFullYear()}-${dataMonth.curDate.getMonth() + 1}-${dataMonth.curDate.getDate()}`;
    }
    if (target.innerHTML === "周") {
      index = 1;
      let index2 = dataMonth.getCurWeekFirstDayIndex();
      switchLabel.innerHTML = `${dataMonth.dateArr[index2].month}-${dataMonth.dateArr[index2].day}~${dataMonth.dateArr[index2 + 6].month}-${dataMonth.dateArr[index2 + 6].day}`;
    } else if (target.innerHTML === "月") {
      index = 2;
      switchLabel.innerHTML = `${dataMonth.curDate.getFullYear()}年${dataMonth.curDate.getMonth() + 1}月`;
    }
    Helper.$id(arr[index]).style.zIndex = "20";
  };
  let gotoCurDay = async () => {
    let switchLabel = Helper.$id("switchLabel");
    let nowDate = new Date();
    if (nowDate.getFullYear() === dataMonth.curDate.getFullYear() && nowDate.getMonth() === dataMonth.curDate.getMonth() && nowDate.getDate() === dataMonth.curDate.getDate()) {
      return;
    } else if (nowDate.getFullYear() != dataMonth.curDate.getFullYear() || nowDate.getMonth() != dataMonth.curDate.getMonth()) {
      await dataMonth.init();
    } else {
      dataMonth.curDate = nowDate;
    }
    switchLabel.parentElement.nextElementSibling.classList.add("todaySelected");
    switchLabel.innerHTML = `${nowDate.getFullYear()}-${nowDate.getMonth() + 1}-${nowDate.getDate()}`;
    dispatchEvent(new Event("refreshView"));
    Helper.$id("ViewWeek").style.zIndex = "0";
    Helper.$id("ViewMonth").style.zIndex = "0";
    Helper.$id("ViewDay").style.zIndex = "20";
    let dom = switchLabel.parentElement.previousElementSibling;
    dom.children[0].classList.add("selected");
    dom.children[1].classList.remove("selected");
    dom.children[2].classList.remove("selected");
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
  eventer.once("dataReady", () => {
    let index = dataSetting.setting.ViewDefault;
    let dom = Helper.$id("SwitchBtns").firstElementChild;
    switchBtnClick({ target: dom.children[index] });
  });

  return (
    <div id="SwitchBtns">
      <div class="btns navigateBtns" onClick={switchBtnClick}>
        <div>日</div>
        <div>周</div>
        <div>月</div>
      </div>
      <div class="btns dayBtns">
        <div onClick={prevBtnClick}>
          <i class="iconfont icon-zuojiantou"></i>
        </div>
        <div id="switchLabel"></div>
        <div onClick={nextBtnClick}>
          <i class="iconfont icon-youjiantou"></i>
        </div>
      </div>
      <div onClick={gotoCurDay} class="btns today todaySelected">
        今
      </div>
    </div>
  );
}
