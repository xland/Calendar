import React from "./React";
import "./NewJobBox.scss";

export default function() {
  document.addEventListener("DOMContentLoaded", async ()=>{
    let url = new URL(window.location.href)
    let startTime = new Date(parseInt(url.searchParams.get("startTime")))
    let timeBox = document.getElementById("NewJobBox").firstElementChild;
    timeBox.querySelector("#year").innerHTML = startTime.getFullYear().toString();
    timeBox.querySelector("#month").innerHTML = (startTime.getMonth()+1).toString();
    timeBox.querySelector("#date").innerHTML = (startTime.getDate()).toString();
    timeBox.querySelector("#hour0").innerHTML = (startTime.getHours()).toString();
    timeBox.querySelector("#hour1").innerHTML = (startTime.getHours()+1).toString();
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