import React from "jsx-dom";
import "./TitleBarBtns.scss";
export default function () {
  let minimize = async () => {
    let { ipcRenderer } = require("electron");
    await ipcRenderer.invoke("changeWindowState", "minimize");
  };
  let restore = async () => {
    let { ipcRenderer } = require("electron");
    await ipcRenderer.invoke("changeWindowState", "restore");
  };
  let maximize = async () => {
    let { ipcRenderer } = require("electron");
    await ipcRenderer.invoke("changeWindowState", "maximize");
  };
  let close = async () => {
    let { ipcRenderer } = require("electron");
    await ipcRenderer.invoke("changeWindowState", "close");
  };
  let windowStateHandler = (e, state) => {
    let restoreBtn = document.getElementById("restoreBtn") as HTMLElement;
    let maximizeBtn = document.getElementById("maximizeBtn") as HTMLElement;
    if (state === "maximize") {
      restoreBtn.style.display = "";
      maximizeBtn.style.display = "none";
    } else if (state === "unmaximize") {
      restoreBtn.style.display = "none";
      maximizeBtn.style.display = "";
    }
  }
  document.addEventListener("DOMContentLoaded", async ()=>{
    let { ipcRenderer } = require("electron");
    ipcRenderer.addListener("windowStateChanged", windowStateHandler);
    let flag = await ipcRenderer.invoke("getWindowState");
    windowStateHandler(null,flag?"maximize":"unmaximize");
  })

  return <div id="TitleBarBtns">
    <div onClick={minimize}>
      <i class="iconfont icon-minimize"></i>
    </div>
    <div onClick={restore} id="restoreBtn" style="display: none;">
      <i class="iconfont icon-restore"></i>
    </div>
    <div onClick={maximize} id="maximizeBtn">
      <i class="iconfont icon-maximize"></i>
    </div>
    <div onClick={close} id="closeBtn">
      <i class="iconfont icon-close"></i>
    </div>
</div>;
}
