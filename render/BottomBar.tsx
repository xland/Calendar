import React from "./React";
import "./BottomBar.scss";
import SettingDefault from "./SettingDefault";
import SettingDonate from "./SettingDonate";
import SettingLang from "./SettingLang";
import SettingTomato from "./SettingTomato";
import SettingSkin from "./SettingSkin";


export default function () {  
    let closeDrawerBtnClick = ()=>{
        let drawer = document.getElementById("SettingDrawer")
        drawer.style.display = "none"
    }
    let settingBtnClick = (e)=>{
        let target = e.target as HTMLElement
        if(target.tagName === "I"){
            target = target.parentElement
        }
        let prevSelectedDom = document.querySelector(".bottomBtnSelected") as HTMLElement
        if(prevSelectedDom){
            prevSelectedDom.classList.remove("bottomBtnSelected")
        }
        let drawer = document.getElementById("SettingDrawer")
        if(drawer.style.display === "block"){
            if(drawer.firstElementChild.firstElementChild.innerHTML === target.title){
                drawer.style.display = "none"
                return
            }
        }
        target.classList.add("bottomBtnSelected")
        drawer.firstElementChild.firstElementChild.innerHTML = target.title;  
        if(drawer.children.length>1){
            drawer.lastElementChild.remove();   
        }        
        if(target.title === "设置"){
            drawer.appendChild(<SettingDefault></SettingDefault>)
        }else if(target.title === "皮肤"){
            drawer.appendChild(<SettingSkin></SettingSkin>)
        }else if(target.title === "番茄钟"){
            drawer.appendChild(<SettingTomato></SettingTomato>)
        }else if(target.title === "语言"){
            drawer.appendChild(<SettingLang></SettingLang>)
        }else if(target.title === "捐赠（微信）"){
            drawer.appendChild(<SettingDonate></SettingDonate>)
        }
        drawer.style.display = "block"
    }
  return <><div id="BottomBar" onClick={settingBtnClick}>
    <div class="bottomBtn" title="设置">
        <i class="iconfont icon-setting"></i>
    </div>
    <div class="bottomBtn" title="皮肤">
        <i class="iconfont icon-pifu"></i>
    </div>
    <div  class="bottomBtn" title="番茄钟">
        <i class="iconfont icon-shijian1"></i>
    </div>
    <div  class="bottomBtn" title="语言">
        <i class="iconfont icon-yuyan"></i>
    </div>
    <div  class="bottomBtn" title="捐赠（微信）">
        <i class="iconfont icon-juanzeng"></i>
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
}