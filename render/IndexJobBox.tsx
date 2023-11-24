import React from "./React";
import "./IndexJobBox.scss";
import { ModelJob } from "../model/ModelJob";

export default function () {
  let loaded = (e: CustomEvent) => {
    let job = e.detail as ModelJob;
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

    let year = startTime.getFullYear();
  };
  let yearOptionMouseWheel = (e: WheelEvent) => {
    let target = e.currentTarget as HTMLElement;
    if (target.classList.contains("optionBox")) {
      let src = target.previousElementSibling.firstElementChild;
      let year = Number(src.innerHTML);
      if (e.deltaY < 0) {
        year -= 3;
      } else {
        year -= 1;
      }
      target.innerHTML = "";
      for (let i = year; i < year + 5; i++) {
        let ele = <div>{i}年</div>;
        if (i === year + 2) {
          ele.classList.add("selectedOption");
        }
        target.append(ele);
      }
      src.innerHTML = (year + 2).toString();
    } else {
      let src = target.firstElementChild;
      let year = Number(src.innerHTML);
      if (e.deltaY < 0) {
        year -= 1;
      } else {
        year += 1;
      }
      src.innerHTML = year.toString();
    }
  };
  let yearClick = (e: MouseEvent) => {
    let target = e.currentTarget as HTMLElement;
    let year = Number(target.firstElementChild.innerHTML);
    target = target.nextElementSibling as HTMLElement;
    target.innerHTML = "";
    for (let i = -2; i < 3; i++) {
      let ele = <div>{year + i}年</div>;
      if (i === 0) {
        ele.classList.add("selectedOption");
      }
      target.append(ele);
    }
    target.style.display = "block";
    target.focus();
  };
  let optionBoxBlur = (e: MouseEvent) => {
    let target = e.currentTarget as HTMLElement;
    target.style.display = "none";
  };
  return (
    <div id="IndexJobBox" onLoaded={loaded}>
      <div class="timeBox">
        <div>
          <div class="rowItem" onMouseWheel={yearOptionMouseWheel} onClick={yearClick}>
            <span id="year"></span>年
          </div>
          <div tabindex="-1" class="optionBox" onMouseWheel={yearOptionMouseWheel} onBlur={optionBoxBlur}></div>
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
      <div class="textareaBox">
        <textarea id="jobInfo" spellCheck={false} placeholder="事件内容"></textarea>
        <input id="jobId" type="hidden" />
      </div>
    </div>
  );
}
