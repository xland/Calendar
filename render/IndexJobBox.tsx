import React from "./React";
import "./IndexJobBox.scss";
import { ModelJob } from "../model/ModelJob";
import { Helper } from "../common/Helper";

export default function () {
  let loaded = (e: CustomEvent) => {
    let job = e.detail as ModelJob;
    let startTime = new Date(job.StartTime);
    let endTime = new Date(job.EndTime);

    let dom = Helper.$id("IndexJobBox").firstElementChild as HTMLElement;
    dom.children[0].innerHTML = startTime.getFullYear().toString() + "年";
    dom.children[1].innerHTML = (startTime.getMonth() + 1).toString() + "月";
    dom.children[2].innerHTML = startTime.getDate().toString() + "日";
    dom.children[3].innerHTML = startTime.getHours().toString().padStart(2, "0") + "时";
    dom.children[4].innerHTML = startTime.getMinutes().toString().padStart(2, "0") + "分";
    dom.children[6].innerHTML = endTime.getHours().toString().padStart(2, "0") + "时";
    dom.children[7].innerHTML = endTime.getMinutes().toString().padStart(2, "0") + "分";
    dom = dom.nextElementSibling as HTMLElement;
    dom.innerHTML = dom.nextElementSibling.children[job.RepeatType].innerHTML;
    let taEle = Helper.$id("jobInfo") as HTMLTextAreaElement;
    taEle.value = job.JobInfo;
    let inputId = taEle.nextElementSibling as HTMLInputElement;
    inputId.value = job.Id;
    let arr = ["日", "一", "二", "三", "四", "五", "六"];
    dom = taEle.parentElement.previousElementSibling as HTMLElement;
    dom.children[3].innerHTML = `每周${arr[startTime.getDay()]}`;
    dom.children[4].innerHTML = `每月第${startTime.getDate()}天`;
    dom.children[5].innerHTML = `每年${startTime.getMonth() + 1}月${startTime.getDate()}日`;
  };
  let timeItemClick = (e: MouseEvent) => {
    let target = e.target as HTMLElement;
    if (!target.classList.contains("timeItem")) return;
    //todo 显示输入框
  };
  let getCurMonthMaxDate = (dom: HTMLElement) => {
    let year = dom.children[0].innerHTML;
    let month = dom.children[1].innerHTML;
    year = year.substring(0, year.length - 1);
    month = month.substring(0, month.length - 1);
    let dateObj = new Date(Number(year), Number(month), 0);
    let result = dateObj.getDate();
    return result;
  };
  let currectCurMonthDate = (date: number, dom: HTMLElement) => {
    let str = dom.children[2].innerHTML;
    str = str.substring(0, str.length - 1);
    if (Number(str) > date) {
      dom.children[2].innerHTML = date.toString() + "日";
    }
  };
  let timeItemWheel = (e: WheelEvent) => {
    let target = e.target as HTMLElement;
    if (!target.classList.contains("timeItem")) return;
    let id = target.getAttribute("id");
    let val = e.deltaY < 0 ? -1 : 1;
    let str = target.innerHTML;
    let num = Number(str.substring(0, str.length - 1)) + val;
    if (id === "year") {
      target.innerHTML = num.toString() + "年";
      let max = getCurMonthMaxDate(e.currentTarget as HTMLElement);
      currectCurMonthDate(max, e.currentTarget as HTMLElement);
    } else if (id === "month") {
      if (num < 1) num = 12;
      if (num > 12) num = 1;
      target.innerHTML = num.toString() + "月";
      let max = getCurMonthMaxDate(e.currentTarget as HTMLElement);
      currectCurMonthDate(max, e.currentTarget as HTMLElement);
    } else if (id === "date") {
      let max = getCurMonthMaxDate(e.currentTarget as HTMLElement);
      if (num < 1) num = max;
      if (num > max) num = 1;
      target.innerHTML = num.toString() + "日";
    } else if (id.startsWith("hour")) {
      if (num < 0) num = 59;
      if (num > 59) num = 0;
      target.innerHTML = num.toString().padStart(2, "0") + "时";
    } else if (id.startsWith("minute")) {
      if (num < 0) num = 59;
      if (num > 59) num = 0;
      target.innerHTML = num.toString().padStart(2, "0") + "分";
    }
  };
  let repeatBtnClick = (e: MouseEvent) => {
    let target = e.currentTarget as HTMLElement;
    target = target.nextElementSibling as HTMLElement;
    target.style.display = "block";
    target.focus();
  };
  let selectOptionClick = (e: MouseEvent) => {
    let target = e.target as HTMLElement;
    let val = target.innerHTML;
    target = e.currentTarget as HTMLElement;
    target.style.display = "none";
    target.previousElementSibling.innerHTML = val;
  };
  let selectOptionBlur = (e: MouseEvent) => {
    let target = e.currentTarget as HTMLElement;
    target.style.display = "none";
  };
  return (
    <div id="IndexJobBox" onLoaded={loaded}>
      <div class="timeBox" onClick={timeItemClick} onMouseWheel={timeItemWheel}>
        <div class="timeItem" id="year" style="width:60px"></div>
        <div class="timeItem" id="month"></div>
        <div class="timeItem" id="date"></div>
        <div class="timeItem" id="hour0"></div>
        <div class="timeItem" id="minute0"></div>
        <div class="timeBlank">至</div>
        <div class="timeItem" id="hour1"></div>
        <div class="timeItem" id="minute1"></div>
        <div style="display:inline-block">（鼠标滚轮控制）</div>
      </div>
      <div class="repeatBtn" onClick={repeatBtnClick}>
        不重复
      </div>
      <div tabindex="-1" id="selectOption" onClick={selectOptionClick} onBlur={selectOptionBlur}>
        <div>不重复</div>
        <div>每天</div>
        <div>每个工作日</div>
        <div></div>
        <div></div>
        <div></div>
      </div>
      <div class="textareaBox">
        <textarea id="jobInfo" spellCheck={false} placeholder="日程内容"></textarea>
        <input id="jobId" type="hidden" />
      </div>
    </div>
  );
}
