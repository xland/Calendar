import React from "./React";
import "./IndexJobBox.scss";
import { ModelJob } from "../model/ModelJob";

export default function () {
  let loaded = (e: CustomEvent) => {
    let job = e.detail as ModelJob;
    let startTime = new Date(job.StartTime);
    let endTime = new Date(job.EndTime);
    let dom = document.getElementById("IndexJobBox").firstElementChild.firstElementChild as HTMLElement;
    dom.innerHTML = startTime.getFullYear().toString() + "年";
    dom = dom.nextElementSibling as HTMLElement;
    dom.innerHTML = (startTime.getMonth() + 1).toString() + "月";
    dom = dom.nextElementSibling as HTMLElement;
    dom.innerHTML = startTime.getDate().toString() + "日 &nbsp;";
    dom = dom.nextElementSibling as HTMLElement;
    dom.innerHTML = startTime.getHours().toString().padStart(2, "0") + ":";
    dom = dom.nextElementSibling as HTMLElement;
    dom.innerHTML = startTime.getMinutes().toString().padStart(2, "0") + "——";
    dom = dom.nextElementSibling as HTMLElement;
    dom.innerHTML = endTime.getHours().toString().padStart(2, "0") + ":";
    dom = dom.nextElementSibling as HTMLElement;
    dom.innerHTML = endTime.getMinutes().toString().padStart(2, "0");
    let taEle = document.getElementById("jobInfo") as HTMLTextAreaElement;
    taEle.value = job.JobInfo;
    let inputId = taEle.nextElementSibling as HTMLInputElement;
    inputId.value = job.Id;

    dom = dom.parentElement.nextElementSibling.firstElementChild as HTMLElement;
    for (let i = 0; i < 5; i++) {
      dom.children[i].innerHTML = (startTime.getFullYear() - 2 + i).toString() + "年";
    }
    dom = dom.nextElementSibling as HTMLElement;
    let month = startTime.getMonth() - 1;
    for (let i = 0; i < 5; i++) {
      dom.children[i].innerHTML = month.toString() + "月";
      month += 1;
      month = month > 12 ? 1 : month;
    }
    dom = dom.nextElementSibling as HTMLElement;
    let date = startTime.getDate();
    let maxDate = new Date(startTime);
    maxDate.setMonth(maxDate.getMonth() + 1);
    maxDate.setDate(0);
    let max = maxDate.getDate();
    for (let i = 0; i < 5; i++) {
      dom.children[i].innerHTML = date.toString() + "日";
      date += 1;
      date = date > max ? 1 : date;
    }
    dom = dom.nextElementSibling as HTMLElement;
    let hour = startTime.getHours() - 2;
    hour = hour < 0 ? 24 + hour : hour;
    for (let i = 0; i < 5; i++) {
      dom.children[i].innerHTML = hour.toString() + "时";
      hour += 1;
      hour = hour >= 24 ? 0 : hour;
    }
    dom = dom.nextElementSibling as HTMLElement;
    let minute = startTime.getMinutes() - 2;
    minute = minute < 0 ? 60 + minute : minute;
    for (let i = 0; i < 5; i++) {
      dom.children[i].innerHTML = minute.toString() + "分";
      minute += 1;
      minute = minute > 59 ? 0 : minute;
    }

    dom = dom.nextElementSibling.nextElementSibling as HTMLElement;
    hour = endTime.getHours() - 2;
    hour = hour < 0 ? 24 + hour : hour;
    for (let i = 0; i < 5; i++) {
      dom.children[i].innerHTML = hour.toString() + "时";
      hour += 1;
      hour = hour >= 24 ? 0 : hour;
    }
    dom = dom.nextElementSibling as HTMLElement;
    minute = endTime.getMinutes() - 2;
    minute = minute < 0 ? 60 + minute : minute;
    for (let i = 0; i < 5; i++) {
      dom.children[i].innerHTML = minute.toString() + "分";
      minute += 1;
      minute = minute > 59 ? 0 : minute;
    }
  };
  let timeBtnClick = (e: MouseEvent) => {
    let target = e.currentTarget as HTMLElement;
    target = target.nextElementSibling as HTMLElement;
    target.style.display = "block";
    target.focus();
  };
  let selectOptionBlur = (e: Event) => {
    let target = e.currentTarget as HTMLElement;
    target.style.display = "none";
  };
  let yearMouseWheel = (e: WheelEvent) => {
    let target = e.currentTarget as HTMLElement;
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
      <div class="selectBtn" onClick={timeBtnClick}>
        <span id="year"></span>
        <span id="month"></span>
        <span id="date"></span>
        <span id="hour0"></span>
        <span id="minute0">00</span>
        <span id="hour1"></span>
        <span id="minute1">00</span>
      </div>
      <div class="selectOption" tabindex="-1" onBlur={selectOptionBlur}>
        <div class="selectColumn" style="width:52px" onMouseWheel={yearMouseWheel}>
          <div></div>
          <div></div>
          <div class="selectCell"></div>
          <div></div>
          <div></div>
        </div>
        <div class="selectColumn">
          <div></div>
          <div></div>
          <div class="selectCell"></div>
          <div></div>
          <div></div>
        </div>
        <div class="selectColumn">
          <div></div>
          <div></div>
          <div class="selectCell"></div>
          <div></div>
          <div></div>
        </div>
        <div class="selectColumn">
          <div></div>
          <div></div>
          <div class="selectCell"></div>
          <div></div>
          <div></div>
        </div>
        <div class="selectColumn">
          <div></div>
          <div></div>
          <div class="selectCell"></div>
          <div></div>
          <div></div>
        </div>
        <div class="selectColumn selectColumnSpan">
          <div>-</div>
          <div>-</div>
          <div class="selectCell">-</div>
          <div>-</div>
          <div>-</div>
        </div>
        <div class="selectColumn">
          <div></div>
          <div></div>
          <div class="selectCell"></div>
          <div></div>
          <div></div>
        </div>
        <div class="selectColumn">
          <div></div>
          <div></div>
          <div class="selectCell"></div>
          <div></div>
          <div></div>
        </div>
      </div>
      <div class="selectBtn">不重复</div>
      <div class="textareaBox">
        <textarea id="jobInfo" spellCheck={false} placeholder="事件内容"></textarea>
        <input id="jobId" type="hidden" />
      </div>
    </div>
  );
}
