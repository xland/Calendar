import React from "./React";
import "./BottomBar.scss";
import SettingDefault from "./SettingDefault";
import SettingDonate from "./SettingDonate";
import SettingAuthor from "./SettingAuthor";
import { Helper } from "./common/Helper";

export default function () {
  let closeDrawerBtnClick = () => {
    let drawer = Helper.$id("SettingDrawer");
    drawer.style.display = "none";
    let btn = drawer.previousElementSibling.querySelector(".bottomBtnSelected") as HTMLElement;
    btn.classList.remove("bottomBtnSelected");
  };
  let settingBtnClick = (e) => {
    let target = e.target as HTMLElement;
    if (target.tagName === "I") {
      target = target.parentElement;
    }
    let prevSelectedDom = document.querySelector(".bottomBtnSelected") as HTMLElement;
    if (prevSelectedDom) {
      prevSelectedDom.classList.remove("bottomBtnSelected");
    }
    let drawer = Helper.$id("SettingDrawer");
    if (drawer.style.display === "block") {
      if (drawer.firstElementChild.firstElementChild.innerHTML === target.title) {
        drawer.style.display = "none";
        return;
      }
    }
    target.classList.add("bottomBtnSelected");
    drawer.firstElementChild.firstElementChild.innerHTML = target.title;
    if (drawer.children.length > 1) {
      drawer.lastElementChild.remove();
    }
    if (target.title === "设置") {
      drawer.appendChild(<SettingDefault></SettingDefault>);
    } else if (target.title === "作者（微信）") {
      drawer.appendChild(<SettingAuthor></SettingAuthor>);
    } else if (target.title === "捐赠（微信）") {
      drawer.appendChild(<SettingDonate></SettingDonate>);
    }
    document.querySelector(".settingBox").dispatchEvent(new Event("loaded"));
    drawer.style.display = "block";
  };
  return (
    <>
      <div id="BottomBar" onClick={settingBtnClick}>
        <div class="bottomBtn" title="设置">
          <i class="iconfont icon-setting"></i>
        </div>
        <div class="bottomBtn" title="作者（微信）">
          <i class="iconfont icon-author"></i>
        </div>
        <div class="bottomBtn" title="捐赠（微信）">
          <i class="iconfont icon-heart"></i>
        </div>
      </div>
      <div id="SettingDrawer" style="display:none">
        <div class="drawerTitle">
          <div></div>
          <div onClick={closeDrawerBtnClick}>
            <i class="iconfont icon-close"></i>
          </div>
        </div>
      </div>
    </>
  );
}
