import React from "./React";
import "./BottomBar.scss";
import SettingDefault from "./SettingDefault";
import SettingDonate from "./SettingDonate";
import SettingLang from "./SettingLang";
import SettingTomato from "./SettingTomato";
import SettingSkin from "./SettingSkin";


export default function () {  
    let bottomBtnClick = (id:string)=>{
        document.querySelectorAll(".drawerDom").forEach(v=>{
            (v as HTMLElement).style.display = "none"
        })
        let target = document.getElementById(id);
        target.style.display = target.style.display === "none"?"block":"none"
    }
    let closeDrawerBtnClick = ()=>{

    }
    let settingBtnClick = (e)=>{
        let target = e.target as HTMLElement
        if(target.tagName === "I"){
            target = target.parentElement
        }
        let drawer = document.getElementById("SettingDrawer")
        drawer.firstElementChild.firstElementChild.innerHTML = target.title;        
        if(target.title === "设置"){
            drawer.appendChild(<SettingDefault></SettingDefault>)
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