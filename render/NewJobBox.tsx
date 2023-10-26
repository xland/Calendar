import React from "jsx-dom";
import "./NewJobBox.scss";
import { ModelJob } from "../model/ModelJob";

export class NewJobBox extends React.Component {
  static getData(){
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
  render() {
  return <div id="NewJobBox">
  <div class="timeBox">
    <div><span id="year">2023</span>年</div>
    <div><span id="month">10</span>月</div>
    <div><span id="date">24</span>日</div>
    <div style="margin-left:3px"><span id="hour0">14</span>时</div>
    <div style="margin-right:3px"><span id="minute0">15</span>分</div>
    ——
    <div style="margin-left:3px"><span id="hour1">14</span>时</div>
    <div><span id="minute1">30</span>分</div>
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
}