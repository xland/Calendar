import React from "jsx-dom";
import "./SwitchBtns.scss";
export default function () {
  let getId = (dom)=>{
    if(dom.innerHTML === "日"){
      return "ViewDay"
    }else if(dom.innerHTML === "周"){
      return "ViewWeek"
    }else{
      return "ViewMonth"
    }
  }
  let switchBtnClick = (e)=>{
    let target = e.target as HTMLElement
    if(target.classList.contains("selected")) return;
    let selectedDom = target.parentElement.querySelector(".selected") as HTMLElement
    selectedDom.classList.remove("selected")
    let id = getId(selectedDom)
    document.getElementById(id).style.display = "none"
    target.classList.add("selected")
    id = getId(target);
    document.getElementById(id).style.display = "flex"
  }
  return <div id="SwitchBtns">
    <div class="btns navigateBtns" onClick={switchBtnClick}>
        <div>日</div>
        <div class="selected">周</div>
        <div>月</div>
    </div>
    <div class="btns dayBtns">
        <div><i class="iconfont icon-zuojiantou"></i></div>
        <div>2011-11-11</div>
        <div><i class="iconfont icon-youjiantou"></i></div>
    </div>
  </div>;
}