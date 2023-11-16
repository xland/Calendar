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
        let drawer = document.getElementById("SettingDrawer")
        drawer.firstElementChild.firstElementChild.innerHTML = target.title;  
        let contentBox = drawer.lastElementChild;
        contentBox.innerHTML = ""      
        if(target.title === "设置"){
            contentBox.appendChild(<SettingDefault></SettingDefault>)
        }else if(target.title === "皮肤"){
            contentBox.appendChild(<SettingSkin></SettingSkin>)
        }else if(target.title === "番茄钟"){
            contentBox.appendChild(<SettingTomato></SettingTomato>)
        }else if(target.title === "语言"){
            contentBox.appendChild(<SettingLang></SettingLang>)
        }else if(target.title === "捐赠（微信）"){
            contentBox.appendChild(<SettingDonate></SettingDonate>)
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
        <div class="drawerContent">

        </div>
    </div>
    </>
}