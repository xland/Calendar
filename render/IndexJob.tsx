import React from "./React";
import "./IndexJob.scss";
import TitleBarBtns from "./TitleBarBtns";
import IndexJobBox from "./IndexJobBox";
import ColorGet from "./ColorGet";
import { ModelJob } from "../model/ModelJob";
import { eventer } from "../common/eventer";
function App() {  
  let getStyle = (alpha = 1)=>{
    let url = new URL(window.location.href);
    let colorIndex = parseInt(url.searchParams.get("colorIndex"))
    return `background:rgba(${ColorGet(colorIndex)},${alpha});`
  }

  let getData = ()=>{
    let timeBox = document.getElementById("IndexJobBox").firstElementChild;
    let year = parseInt(timeBox.querySelector("#year").innerHTML);
    let month = parseInt(timeBox.querySelector("#month").innerHTML);
    let date = parseInt(timeBox.querySelector("#date").innerHTML);
    let hour0 = parseInt(timeBox.querySelector("#hour0").innerHTML);
    let minute0 = parseInt(timeBox.querySelector("#minute0").innerHTML);
    let hour1 = parseInt(timeBox.querySelector("#hour1").innerHTML);
    let minute1 = parseInt(timeBox.querySelector("#minute1").innerHTML);
    let job = new ModelJob();
    job.StartTime = new Date(year,month-1,date,hour0,minute0,0,0).getTime();
    job.EndTime = new Date(year,month-1,date,hour1,minute1,0,0).getTime();
    job.RepeatType = 0;
    job.AlertBefore = parseInt((document.getElementById("alertBefore") as HTMLInputElement).value);
    job.JobInfo = (document.getElementById("jobInfo") as HTMLTextAreaElement).value;    
    return job;
  }

  let save = async ()=>{
    let url = new URL(window.location.href);
    let data = getData();
    data.ColorIndex = parseInt(url.searchParams.get("colorIndex"))
    let { ipcRenderer } = require("electron");
    await ipcRenderer.invoke("saveToDb","Job",data);
  }
  return <>
      <div class="titleBar" style={getStyle(0.1)}>
        <div class="title">增加日程</div>
        <TitleBarBtns></TitleBarBtns>
      </div>
      <IndexJobBox></IndexJobBox>
      <div class="btnBox">
        <div class="btnSave" 
             style={`${getStyle()}color:#fff`} 
             //@ts-ignore
             onMouseOver={e=>e.target.style = `${getStyle(0.9)}color:#fff;`}
             //@ts-ignore
             onMouseOut={e=>e.target.style = `${getStyle()}color:#fff;`}
             onClick={save}
             >保存</div>
      </div>
    </>
}

document.addEventListener("DOMContentLoaded", async ()=>{
  let url = new URL(window.location.href);
  let editId = url.searchParams.get("editId")
  let job:ModelJob;
  if(editId){
    let {ipcRenderer} = require("electron")
    job = await ipcRenderer.invoke("getOneData",editId);
  }else{
    job = new ModelJob();
    job.ColorIndex = parseInt(url.searchParams.get("colorIndex"))
  }
  document.body.appendChild(<App/>);
  eventer.emit("dataReady",job)
})