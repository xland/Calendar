import React from "./React";
import "./IndexNewJob.scss";
import TitleBarBtns from "./TitleBarBtns";
import NewJobBox from "./NewJobBox";
import ColorGet from "./ColorGet";
import { ModelJob } from "../model/ModelJob";

function App() {  
  let getStyle = (alpha = 1)=>{
    let url = new URL(window.location.href);
    let colorIndex = parseInt(url.searchParams.get("colorIndex"))
    return `background:rgba(${ColorGet(colorIndex)},${alpha});`
  }

  let getData = ()=>{
    let year = parseInt(document.getElementById("year").innerHTML);
    let month = parseInt(document.getElementById("month").innerHTML);
    let date = parseInt(document.getElementById("date").innerHTML);
    let hour0 = parseInt(document.getElementById("hour0").innerHTML);
    let minute0 = parseInt(document.getElementById("minute0").innerHTML);
    let hour1 = parseInt(document.getElementById("hour1").innerHTML);
    let minute1 = parseInt(document.getElementById("minute1").innerHTML);
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
  return (
    <>
      <div class="titleBar" style={getStyle(0.1)}>
        <div class="title">增加日程</div>
        <TitleBarBtns></TitleBarBtns>
      </div>
      <NewJobBox></NewJobBox>
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
  );
}
document.body.appendChild(<App />);