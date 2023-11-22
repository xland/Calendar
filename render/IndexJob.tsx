import React from "./React";
import "./IndexJob.scss";
import TitleBarBtns from "./TitleBarBtns";
import IndexJobBox from "./IndexJobBox";
import ColorGet from "./ColorGet";
import { ModelJob } from "../model/ModelJob";
function App(props) {
  let getStyle = (alpha = 1) => {
    return `background:rgba(${ColorGet(props.colorIndex)},${alpha});`;
  };

  let getData = () => {
    let timeBox = document.getElementById("IndexJobBox").firstElementChild;
    let year = parseInt(timeBox.querySelector("#year").innerHTML);
    let month = parseInt(timeBox.querySelector("#month").innerHTML);
    let date = parseInt(timeBox.querySelector("#date").innerHTML);
    let hour0 = parseInt(timeBox.querySelector("#hour0").innerHTML);
    let minute0 = parseInt(timeBox.querySelector("#minute0").innerHTML);
    let hour1 = parseInt(timeBox.querySelector("#hour1").innerHTML);
    let minute1 = parseInt(timeBox.querySelector("#minute1").innerHTML);
    let job = new ModelJob();
    job.StartTime = new Date(year, month - 1, date, hour0, minute0, 0, 0).getTime();
    job.EndTime = new Date(year, month - 1, date, hour1, minute1, 0, 0).getTime();
    job.RepeatType = 0;
    let taEle = document.getElementById("jobInfo") as HTMLTextAreaElement;
    let inputId = taEle.nextElementSibling as HTMLInputElement;
    job.JobInfo = taEle.value;
    job.Id = inputId.value;
    job.ColorIndex = props.colorIndex;
    return job;
  };

  let save = async () => {
    let job = getData();
    let { ipcRenderer } = require("electron");
    if (job.Id) {
      let sql = `Update Job set JobInfo = ? ,StartTime = ? ,EndTime = ? where Id = ?`;
      await ipcRenderer.invoke("excuteSQL", sql, job.JobInfo, job.StartTime, job.EndTime, job.Id);
    } else {
      await ipcRenderer.invoke("saveToDb", "Job", job);
    }
    let win = window.opener as Window;
    win.dispatchEvent(new Event("saveJobOk"));
    window.close();
  };
  return (
    <>
      <div class="titleBar" style={getStyle(0.1)}>
        <div class="title">增加日程</div>
        <TitleBarBtns></TitleBarBtns>
      </div>
      <IndexJobBox></IndexJobBox>
      <div class="btnBox">
        <div
          class="btnSave"
          style={`${getStyle()}color:#fff`}
          //@ts-ignore
          onMouseOver={(e) => (e.target.style = `${getStyle(0.9)}color:#fff;`)}
          //@ts-ignore
          onMouseOut={(e) => (e.target.style = `${getStyle()}color:#fff;`)}
          onClick={save}
        >
          保存
        </div>
      </div>
    </>
  );
}

document.addEventListener("DOMContentLoaded", async () => {
  let url = new URL(window.location.href);
  let editId = url.searchParams.get("editId");
  let job: ModelJob;
  if (editId) {
    let { ipcRenderer } = require("electron");
    let jobArr: ModelJob[] = await ipcRenderer.invoke("getData", "SELECT * FROM Job WHERE Id = ?", editId);
    if (jobArr.length) {
      job = jobArr[0];
    }
  } else {
    job = new ModelJob();
    job.StartTime = Number(url.searchParams.get("startTime"));
    job.ColorIndex = Number(url.searchParams.get("colorIndex"));
    job.JobInfo = "";
    job.Id = "";
  }
  document.body.appendChild(<App colorIndex={job.ColorIndex} />);
  let event = new CustomEvent("loaded", { detail: job });
  document.getElementById("IndexJobBox").dispatchEvent(event);
});
