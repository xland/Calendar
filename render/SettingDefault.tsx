import React from "./React";
import "./SettingDefault.scss";
export default function (props) {
  let setCheckBox = (icon: HTMLElement, flag: boolean) => {
    if (flag) {
      icon.classList.remove("icon-uncheck");
      icon.classList.add("icon-check");
    } else {
      icon.classList.remove("icon-check");
      icon.classList.add("icon-uncheck");
    }
  };
  let openAtLoginClick = async (e: MouseEvent) => {
    let icon = document.getElementById("openAtLoginIcon");
    let flag = !icon.classList.contains("icon-check");
    let { ipcRenderer } = require("electron");
    await ipcRenderer.invoke("setOpenAtLogin", flag);
    setCheckBox(icon, flag);
    return false;
  };
  let loaded = async () => {
    let { ipcRenderer } = require("electron");
    let result = await ipcRenderer.invoke("getSetting");
    let icon = document.getElementById("openAtLoginIcon");
    setCheckBox(icon, result.openAtLogin);
  };
  return (
    <div class="settingBox" onLoaded={loaded}>
      <div class="settingRow" onClick={openAtLoginClick}>
        <div>
          <i id="openAtLoginIcon" class="iconfont icon-uncheck"></i>
        </div>
        <div>开机自启动</div>
      </div>
      <div class="settingRow">
        <div>
          <i class="iconfont icon-uncheck"></i>
        </div>
        <div>显示农历</div>
      </div>
      <div class="settingRow">
        <div>
          <i class="iconfont icon-uncheck"></i>
        </div>
        <div>压缩数据库</div>
      </div>
    </div>
  );
}
