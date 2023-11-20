import React from "./React";
import "./IndexJobBox.scss";
import { eventer } from "../common/eventer";
import { ModelJob } from "../model/ModelJob";

export default function () {
  eventer.once("dataReady", (job: ModelJob) => {
    let startTime = new Date(job.StartTime);
    let timeBox = document.getElementById("IndexJobBox").firstElementChild;
    timeBox.querySelector("#year").innerHTML = startTime.getFullYear().toString();
    timeBox.querySelector("#month").innerHTML = (startTime.getMonth() + 1).toString();
    timeBox.querySelector("#date").innerHTML = startTime.getDate().toString();
    timeBox.querySelector("#hour0").innerHTML = startTime.getHours().toString();
    timeBox.querySelector("#hour1").innerHTML = (startTime.getHours() + 1).toString();
    let taEle = document.getElementById("jobInfo") as HTMLTextAreaElement;
    taEle.value = job.JobInfo;
    let inputId = taEle.nextElementSibling as HTMLInputElement;
    inputId.value = job.Id;
  });
  return (
    <div id="IndexJobBox">
      <div class="timeBox">
        <div>
          <span id="year"></span>年
        </div>
        <div>
          <span id="month"></span>月
        </div>
        <div>
          <span id="date"></span>日
        </div>
        <div style="margin-left:3px">
          <span id="hour0"></span>时
        </div>
        <div style="margin-right:3px">
          <span id="minute0">00</span>分
        </div>
        ——
        <div style="margin-left:3px">
          <span id="hour1"></span>时
        </div>
        <div>
          <span id="minute1">00</span>分
        </div>
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
        <input id="jobId" type="hidden" />
      </div>
    </div>
  );
}
