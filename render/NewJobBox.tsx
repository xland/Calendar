import React from "./React";
import "./NewJobBox.scss";
import { ModelJob } from "../model/ModelJob";

export default function() {
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
  document.addEventListener("DOMContentLoaded", async ()=>{
    let url = new URL(window.location.href)
    let startTime = new Date(parseInt(url.searchParams.get("startTime")))
    document.getElementById("year").innerHTML = startTime.getFullYear().toString();
    document.getElementById("month").innerHTML = (startTime.getMonth()+1).toString();
    document.getElementById("date").innerHTML = (startTime.getDate()).toString();
    document.getElementById("hour0").innerHTML = (startTime.getHours()).toString();
    document.getElementById("hour1").innerHTML = (startTime.getHours()+1).toString();
  })
  return <div id="NewJobBox">
  <div class="timeBox">
    <div><span id="year"></span>年</div>
    <div><span id="month"></span>月</div>
    <div><span id="date"></span>日</div>
    <div style="margin-left:3px"><span id="hour0"></span>时</div>
    <div style="margin-right:3px"><span id="minute0">00</span>分</div>
    ——
    <div style="margin-left:3px"><span id="hour1"></span>时</div>
    <div><span id="minute1">00</span>分</div>
  </div>
  <div>
    <div class="recycleBtn">不重复</div>
  </div>
  <div class="preMins">
    <div style="margin-right:3px">提前</div>
    <input id="alertBefore" type="text" value={"5"} />
    <div style="margin-left:3px">分钟提醒</div>
  </div>
  <div class="textareaBox">
    <textarea id="jobInfo" spellCheck={false} placeholder="事件内容"></textarea>
  </div>
</div>;
}