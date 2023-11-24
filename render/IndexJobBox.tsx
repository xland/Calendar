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
        <div class="selectColumn" style="width:52px">
          <div>2023年</div>
          <div>2023年</div>
          <div class="selectCell">2023年</div>
          <div>2023年</div>
          <div>2023年</div>
        </div>
        <div class="selectColumn">
          <div>1月</div>
          <div>1月</div>
          <div class="selectCell">1月</div>
          <div>1月</div>
          <div>1月</div>
        </div>
        <div class="selectColumn">
          <div>22日</div>
          <div>23日</div>
          <div class="selectCell">23日</div>
          <div>23日</div>
          <div>23日</div>
        </div>
        <div class="selectColumn">
          <div>06时</div>
          <div>06时</div>
          <div class="selectCell">06时</div>
          <div>06时</div>
          <div>06时</div>
        </div>
        <div class="selectColumn">
          <div>33分</div>
          <div>33分</div>
          <div class="selectCell">33分</div>
          <div>33分</div>
          <div>33分</div>
        </div>
        <div class="selectColumn selectColumnSpan">
          <div>-</div>
          <div>-</div>
          <div class="selectCell">-</div>
          <div>-</div>
          <div>-</div>
        </div>
        <div class="selectColumn">
          <div>06时</div>
          <div>06时</div>
          <div class="selectCell">06时</div>
          <div>06时</div>
          <div>06时</div>
        </div>
        <div class="selectColumn">
          <div>33分</div>
          <div>33分</div>
          <div class="selectCell">33分</div>
          <div>33分</div>
          <div>33分</div>
        </div>
      </div>
      <div class="selectBtn">不重复</div>
      <div class="selectOption"></div>
      <div class="textareaBox">
        <textarea id="jobInfo" spellCheck={false} placeholder="事件内容"></textarea>
        <input id="jobId" type="hidden" />
      </div>
    </div>
  );
}
