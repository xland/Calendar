import React from "./React";
import "./IndexAlert.scss";
import TitleBarBtns from "./TitleBarBtns";
import ColorGet from "./ColorGet";
import { ModelJob } from "../model/ModelJob";
import { Helper } from "../common/Helper";
function App(props) {
  let job = props.job as ModelJob;
  let save = () => {
    // let { ipcRenderer } = require("electron");
    // ipcRenderer.invoke("changeWindowState", "close");
  };
  return (
    <>
      <div class="titleBar">
        <div class="title">事务提醒</div>
        <TitleBarBtns></TitleBarBtns>
      </div>
      <div class="content">{job.JobInfo}</div>
      <div class="btnBox">
        <div class="btnSave" onClick={save}>
          知道了
        </div>
      </div>
    </>
  );
}
document.addEventListener("DOMContentLoaded", async () => {
  let url = new URL(window.location.href);
  let id = url.searchParams.get("id");
  // let { ipcRenderer } = require("electron");
  // let [job]: ModelJob[] = await ipcRenderer.invoke("getData", "SELECT * FROM Job WHERE Id = ?", id);
  // document.body.style.setProperty("--color", ColorGet(job.ColorIndex));
  // document.body.appendChild(<App job={job} />);
  // ipcRenderer.invoke("changeWindowState", "show");
});
