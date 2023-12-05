import React from "./React";
import "./IndexAlert.scss";
import TitleBarBtns from "./TitleBarBtns";
import ColorGet from "./ColorGet";
import { ModelJob } from "../model/ModelJob";
import { Helper } from "../common/Helper";
function App(props) {
  return (
    <>
      <div class="titleBar" style={`background:rgba(${ColorGet(props.colorIndex)},0.1);`}>
        <div class="title">增加日程</div>
        <TitleBarBtns></TitleBarBtns>
      </div>
      <div>内容</div>
      <div>
        <div>5分钟后再提醒</div>
        <div>不再提醒</div>
      </div>
    </>
  );
}
document.addEventListener("DOMContentLoaded", async () => {
  let url = new URL(window.location.href);
  let id = url.searchParams.get("id");
  let { ipcRenderer } = require("electron");
  let [job]: ModelJob[] = await ipcRenderer.invoke("getData", "SELECT * FROM Job WHERE Id = ?", id);
  document.body.appendChild(<App colorIndex={job.ColorIndex} />);
  ipcRenderer.invoke("changeWindowState", "show");
});
