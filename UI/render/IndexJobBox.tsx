import React from "./React";
import "./IndexJobBox.scss";
import { ModelJob } from "../model/ModelJob";
import { Helper } from "../common/Helper";

export default function () {
  let loaded = (e: CustomEvent) => {
    let job = e.detail as ModelJob;
    let startTime = new Date(job.StartTime);
    let endTime = new Date(job.EndTime);

    let dom = Helper.$id("IndexJobBox").son0() as HTMLElement;
    dom.children[0].innerHTML = startTime.getFullYear().toString() + "年";
    dom.children[1].innerHTML = (startTime.getMonth() + 1).toString() + "月";
    dom.children[2].innerHTML = startTime.getDate().toString() + "日";
    dom.children[3].innerHTML = startTime.getHours().toString().padStart(2, "0") + "时";
    dom.children[4].innerHTML = startTime.getMinutes().toString().padStart(2, "0") + "分";
    dom.children[6].innerHTML = endTime.getHours().toString().padStart(2, "0") + "时";
    dom.children[7].innerHTML = endTime.getMinutes().toString().padStart(2, "0") + "分";

    let taEle = Helper.$id("jobInfo") as HTMLTextAreaElement;
    taEle.value = job.JobInfo;
    let inputId = taEle.next() as HTMLInputElement;
    inputId.value = job.Id;

    dom = taEle.dad().prev() as HTMLElement;
    let arr = ["日", "一", "二", "三", "四", "五", "六"];
    dom.children[3].innerHTML = `每周${arr[startTime.getDay()]}`;
    dom.children[4].innerHTML = `每月第${startTime.getDate()}天`;
    dom.children[5].innerHTML = `每年${startTime.getMonth() + 1}月${startTime.getDate()}日`;
    dom.prev().innerHTML = dom.children[job.RepeatType].innerHTML;
  };
  let timeItemClick = (e: MouseEvent) => {
    let target = e.target as HTMLElement;
    if (!target.classHas("timeItem")) return;
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
    if (!target.classHas("timeItem")) return;
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
    } else if (id === "hour0") {
      if (num < 0) num = 59;
      if (num > 59) num = 0;
      target.innerHTML = num.toString().padStart(2, "0") + "时";
      let minute0 = target.next();
      let minute0Num = parseInt(minute0.innerHTML);
      let hour1 = minute0.next().next();
      let hour1Num = parseInt(hour1.innerHTML);
      if (hour1Num < num) {
        hour1.innerHTML = num.toString().padStart(2, "0") + "时";
        let minute1 = hour1.next();
        let minute1Num = parseInt(minute1.innerHTML);
        if (minute1Num < minute0Num) {
          minute1.innerHTML = minute0Num.toString().padStart(2, "0") + "分";
        }
      }
    } else if (id === "minute0") {
      if (num < 0) num = 59;
      if (num > 59) num = 0;
      target.innerHTML = num.toString().padStart(2, "0") + "分";
      let hour0 = target.prev();
      let hour0Num = parseInt(hour0.innerHTML);
      let hour1 = target.next().next();
      let hour1Num = parseInt(hour1.innerHTML);
      if (hour1Num === hour0Num) {
        let minute1 = hour1.next();
        let minute1Num = parseInt(minute1.innerHTML);
        if (num > minute1Num) {
          minute1.innerHTML = num.toString().padStart(2, "0") + "分";
        }
      }
    } else if (id === "hour1") {
      if (num < 0) num = 59;
      if (num > 59) num = 0;
      target.innerHTML = num.toString().padStart(2, "0") + "时";
      let minute0 = target.prev().prev();
      let minute0Num = parseInt(minute0.innerHTML);
      let hour0 = minute0.prev();
      let hour0Num = parseInt(hour0.innerHTML);
      if (hour0Num > num) {
        hour0.innerHTML = num.toString().padStart(2, "0") + "时";
        let minute1 = target.next();
        let minute1Num = parseInt(minute1.innerHTML);
        if (minute1Num < minute0Num) {
          minute1.innerHTML = minute0Num.toString().padStart(2, "0") + "分";
        }
      }
    } else if (id === "minute1") {
      if (num < 0) num = 59;
      if (num > 59) num = 0;
      target.innerHTML = num.toString().padStart(2, "0") + "分";
      let hour1 = target.prev();
      let hour1Num = parseInt(hour1.innerHTML);
      let minute0 = hour1.prev().prev();
      let minute0Num = parseInt(minute0.innerHTML);
      let hour0 = minute0.prev();
      let hour0Num = parseInt(hour0.innerHTML);
      if (hour1Num === hour0Num) {
        if (num < minute0Num) {
          minute0.innerHTML = num.toString().padStart(2, "0") + "分";
        }
      }
    }
  };
  let repeatBtnClick = (e: MouseEvent) => {
    let dom = Helper.$id("selectOption");
    let arr = ["日", "一", "二", "三", "四", "五", "六"];
    let timeBox = Helper.$id("IndexJobBox").son0();
    let year = parseInt(timeBox.children[0].innerHTML);
    let month = parseInt(timeBox.children[1].innerHTML);
    let date = parseInt(timeBox.children[2].innerHTML);
    let startTime = new Date(year, month - 1, date);
    dom.children[3].innerHTML = `每周${arr[startTime.getDay()]}`;
    dom.children[4].innerHTML = `每月第${startTime.getDate()}天`;
    dom.children[5].innerHTML = `每年${startTime.getMonth() + 1}月${startTime.getDate()}日`;

    let target = e.currentTarget as HTMLElement;
    target = target.next() as HTMLElement;
    target.style.display = "block";
    target.focus();
  };
  let selectOptionClick = (e: MouseEvent) => {
    let target = e.target as HTMLElement;
    let val = target.innerHTML;
    target = e.currentTarget as HTMLElement;
    target.style.display = "none";
    target.prev().innerHTML = val;
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
