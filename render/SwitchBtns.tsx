import { eventer } from "../common/eventer";
import { dataMonth } from "./DataMonth";
import { dataSetting } from "./DataSetting";
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
      document.getElementById(v).style.zIndex = "0";
    });
    target.classList.add("selected");
    let index = 0;
    if (target.innerHTML === "周") {
      index = 1;
    } else if (target.innerHTML === "月") {
      index = 2;
    }
    document.getElementById(arr[index]).style.zIndex = "20";
  };
  let gotoCurDay = () => {
    let switchLabel = document.getElementById("switchLabel");
    switchLabel.innerHTML = `${dataMonth.curDate.getFullYear()}-${dataMonth.curDate.getMonth() + 1}-${dataMonth.curDate.getDate()}`;
  };
  eventer.once("dataReady", () => {
    let index = dataSetting.setting.ViewDefault;
    let dom = document.getElementById("SwitchBtns").firstElementChild;
    switchBtnClick({ target: dom.children[index] });
    let switchLabel = dom.nextElementSibling.firstElementChild.nextElementSibling;
    switchLabel.innerHTML = `${dataMonth.curDate.getFullYear()}-${dataMonth.curDate.getMonth() + 1}-${dataMonth.curDate.getDate()}`;
  });

  return (
    <div id="SwitchBtns">
      <div class="btns navigateBtns" onClick={switchBtnClick}>
        <div>日</div>
        <div>周</div>
        <div>月</div>
      </div>
      <div class="btns dayBtns">
        <div>
          <i class="iconfont icon-zuojiantou"></i>
        </div>
        <div id="switchLabel"></div>
        <div>
          <i class="iconfont icon-youjiantou"></i>
        </div>
      </div>
      <div onClick={gotoCurDay} class="btns today">
        今
      </div>
    </div>
  );
}
