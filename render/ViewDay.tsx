import React from "./React";
import "./ViewDay.scss";
import Job from "./Job";
import ColorGet from "./ColorGet";
import { eventer } from "../common/eventer";
import { dataMonth } from "./DataMonth";
import debounce from "../common/debounce";

export default function () {
  let colorIndex = 0;
  let addNewJob = (target: HTMLElement) => {
    let startHour: string;
    if (target.classList.contains("hourTag")) {
      startHour = target.innerHTML;
    } else if (target.firstElementChild.classList.contains("hourTag")) {
      startHour = target.firstElementChild.innerHTML;
    }
    if (!startHour) return;
    let hour = parseInt(startHour.split(":")[0]);
    let startTime = new Date();
    startTime.setHours(hour);
    let config = {
      winConfig: { width: 400, height: 300, title: "增加日程", minHeight: 280, minWidth: 380, modal: true },
      extraConfig: {},
    };
    window.open(`/IndexJob.html?colorIndex=${colorIndex}&startTime=${startTime.getTime()}`, "_blank", JSON.stringify(config));
    document.getElementById("ModalMask").style.display = "block";
  };
  let bgLineMouseOver = (e) => {
    let target = e.target as HTMLElement;
    if (target.classList.contains("hourTag")) target = target.parentElement;
    target.style.background = `rgba(${ColorGet(colorIndex)},0.1)`;
  };
  let bgLineMouseOut = (e) => {
    let target = e.target as HTMLElement;
    if (target.classList.contains("hourTag")) target = target.parentElement;
    target.style.background = ``;
  };
  let getData = async () => {
    let now = new Date(dataMonth.curDate.getTime());
    now.setHours(0, 0, 0, 0);
    let start = now.getTime();
    now.setHours(23, 59, 59, 999);
    let end = now.getTime();
    let target = document.getElementById("ViewDay");
    target.querySelectorAll(".Job").forEach((e) => e.remove());
    let useableWidth = target.clientWidth - 90;
    let data = dataMonth.dateArr[dataMonth.getCurDateIndex()].jobs;
    for (let i = 0; i < data.length; i++) {
      let tar = data[i];
      let itemWidth = useableWidth - data.length * 36 + (i + 1) * 36;
      let leftNum = 60;
      let topNum = ((tar.StartTime - start) * 100) / (end - start);
      let bottomNum = ((end - tar.EndTime) * 100) / (end - start);
      let style = `top:${topNum}%;bottom:${bottomNum}%;left:${leftNum}px;width:${itemWidth}px;--color:${ColorGet(tar.ColorIndex)};`;
      target.append(<Job data={tar} style={style}></Job>);
    }
    if (data.length) {
      colorIndex = data[data.length - 1].ColorIndex + 1;
    }
    if (colorIndex > 5) colorIndex = 0;
  };
  let updateItem = async (targeDom: HTMLElement) => {
    let Id = targeDom.getAttribute("id");
    let StartTime = Number(targeDom.dataset.start);
    let EndTime = Number(targeDom.dataset.end);
    let job = dataMonth.getJobById(Id);
    if (job.StartTime === StartTime && job.EndTime === EndTime) {
      return;
    }
    let sql = `Update Job set StartTime = ? ,EndTime = ? where id = ?`;
    let { ipcRenderer } = require("electron");
    await ipcRenderer.invoke("updateData", sql, StartTime, EndTime, Id);
    dispatchEvent(new Event("saveJobOk"));
  };
  let setJobTime = (target: HTMLElement) => {
    let height = target.parentElement.clientHeight;
    let ms = (target.offsetTop / height) * 86400000;
    let now = new Date();
    now.setHours(0, 0, 0, 0);
    now.setMilliseconds(ms);
    target.dataset.start = now.getTime().toString();
    now.setHours(0, 0, 0, 0);
    ms = ((target.offsetTop + target.clientHeight) / height) * 86400000;
    now.setMilliseconds(ms);
    target.dataset.end = now.getTime().toString();
  };
  let updateTimeDom = (target: HTMLElement) => {
    let StartTime = Number(target.dataset.start);
    let EndTime = Number(target.dataset.end);
    let timeDiv = target.querySelector(".timeTop") as HTMLDivElement;
    let dt = new Date(StartTime);
    let minutes = dt.getMinutes();
    // if(dt.getSeconds()>0 || dt.getMilliseconds()>0){
    //     minutes+=1;
    // }
    timeDiv.innerHTML = `${dt.getHours().toString().padStart(2, "0")}:${minutes.toString().padStart(2, "0")}`;
    timeDiv = target.querySelector(".timeBottom") as HTMLDivElement;
    dt = new Date(EndTime);
    minutes = dt.getMinutes();
    // if(dt.getSeconds()>0 || dt.getMilliseconds()>0){
    //     minutes+=1;
    // }
    timeDiv.innerHTML = `${dt.getHours().toString().padStart(2, "0")}:${minutes.toString().padStart(2, "0")}`;
  };
  let onMouseOver = (e) => {
    let target = e.target as HTMLElement;
    if (target.classList.contains("dragger")) {
      target.style.background = `rgb(var(--color))`;
    }
  };
  let onMouseOut = (e) => {
    let target = e.target as HTMLElement;
    if (target.classList.contains("dragger")) {
      target.style.background = `none`;
    }
  };
  let draggerTopMove = (target: HTMLElement, top: number) => {
    if (top < 0) top = 0;
    let height = target.offsetTop + target.clientHeight - top;
    if (height < 12) {
      return 0;
    }
    target.style.top = top + "px";
    if (height < 28) {
      target.lastElementChild.innerHTML = "";
      target.querySelectorAll(".time").forEach((v) => (v.innerHTML = ""));
      return 1;
    }
    target.lastElementChild.innerHTML = target.dataset.text;
    return 2;
  };
  let draggerBottomMove = (target: HTMLElement, bottom: number) => {
    if (bottom < 0) bottom = 0;
    let height = target.parentElement.clientHeight - target.offsetTop - bottom;
    if (height < 12) {
      return 0;
    }
    target.style.bottom = bottom + "px";
    if (height < 28) {
      target.lastElementChild.innerHTML = "";
      target.querySelectorAll(".time").forEach((v) => (v.innerHTML = ""));
      return 1;
    }
    target.lastElementChild.innerHTML = target.dataset.text;
    return 2;
  };
  let onMouseDown = (e: MouseEvent) => {
    if (e.button != 0) return;
    let target = e.target as HTMLElement;
    if (target.classList.contains("bgLine")) {
      addNewJob(target);
      return;
    } else if (target.classList.contains("dragger")) {
      document.querySelectorAll(".jobSelected").forEach((v) => v.classList.remove("jobSelected"));
      target.parentElement.classList.add("jobSelected");
      if (target.classList.contains("draggerSelected")) {
        target.classList.remove("draggerSelected");
      } else {
        document.querySelectorAll(".draggerSelected").forEach((v) => v.classList.remove("draggerSelected"));
        target.classList.add("draggerSelected");
      }
    } else if (target.classList.contains("jobInfo")) {
      document.querySelectorAll(".jobSelected").forEach((v) => v.classList.remove("jobSelected"));
      document.querySelectorAll(".draggerSelected").forEach((v) => v.classList.remove("draggerSelected"));
      target.parentElement.classList.add("jobSelected");
    } else {
      return;
    }
    let oldY = e.y;
    let oldHeight = target.parentElement.clientHeight;
    let documentMouseMove = (e) => {
      if (target.classList.contains("draggerTop")) {
        target.style.background = target.parentElement.style.borderColor;
        let ppE = target.parentElement.parentElement;
        ppE.style.cursor = "ns-resize";
        draggerTopMove(target.parentElement, e.y - ppE.offsetTop);
        setJobTime(target.parentElement);
        updateTimeDom(target.parentElement);
      } else if (target.classList.contains("draggerBottom")) {
        target.style.background = target.parentElement.style.borderColor;
        let ppE = target.parentElement.parentElement;
        ppE.style.cursor = "ns-resize";
        draggerBottomMove(target.parentElement, ppE.clientHeight + ppE.offsetTop - e.y);
        setJobTime(target.parentElement);
        updateTimeDom(target.parentElement);
      } else if (target.classList.contains("jobInfo")) {
        let span = e.y - oldY;
        let pE = target.parentElement;
        let top = pE.offsetTop + span;
        oldY = e.y;
        if (top < 0) return;
        if (pE.parentElement.clientHeight - oldHeight - top - 1 < 0) return;
        pE.style.top = top + "px";
        let bottom = pE.parentElement.clientHeight - oldHeight - pE.offsetTop - 1;
        pE.style.bottom = bottom + "px";
        setJobTime(pE);
        updateTimeDom(pE);
      }
    };
    let documentMouseUp = (e) => {
      document.removeEventListener("mousemove", documentMouseMove);
      document.removeEventListener("mouseup", documentMouseUp);
      if (target.classList.contains("dragger")) {
        target.style.background = `none`;
        target.parentElement.parentElement.style.cursor = "pointer";
        updateItem(target.parentElement);
      } else {
        updateItem(target.parentElement);
      }
      target = null;
    };
    document.addEventListener("mousemove", documentMouseMove);
    document.addEventListener("mouseup", documentMouseUp);
    e.preventDefault();
    return false;
  };
  /**
   * 使用键盘快捷键移动Job
   * @param e
   * @returns
   */
  let moveJobByKey = (e: KeyboardEvent) => {
    if (e.key === "Escape") {
      document.querySelectorAll(".draggerSelected").forEach((v) => v.classList.remove("draggerSelected"));
      document.querySelectorAll(".jobSelected").forEach((v) => v.classList.remove("jobSelected"));
      return;
    }
    if (e.ctrlKey && (e.key === "ArrowUp" || e.key === "ArrowDown")) {
      let stepVal = e.key === "ArrowUp" ? -1 : 1;
      let dragger = document.querySelector(".draggerSelected") as HTMLDivElement;
      if (dragger) {
        let job = dragger.parentElement;
        let t = new Date(); //todo
        let msHeight = job.parentElement.clientHeight / 86400000;
        if (dragger.classList.contains("draggerTop")) {
          let start = Number(job.dataset.start);
          let startTime = new Date(start);
          startTime.setMinutes(startTime.getMinutes() + stepVal, 0, 0);
          t.setHours(0, 0, 0, 0);
          if (startTime < t) {
            return;
          }
          job.dataset.editing = "true";
          let top = msHeight * (startTime.getTime() - t.getTime());
          let r = draggerTopMove(job, top);
          if (r > 0) {
            job.dataset.start = startTime.getTime().toString();
            if (r > 1) {
              updateTimeDom(job);
            }
          }
        } else {
          let end = Number(job.dataset.end);
          let endTime = new Date(end);
          endTime.setMinutes(endTime.getMinutes() + stepVal, 0, 0);
          t.setHours(23, 59, 59, 999);
          if (endTime > t) {
            return;
          }
          job.dataset.editing = "true";
          let bottom = msHeight * (t.getTime() - endTime.getTime());
          let r = draggerBottomMove(job, bottom);
          if (r > 0) {
            job.dataset.end = endTime.getTime().toString();
            if (r > 1) {
              updateTimeDom(job);
            }
          }
        }
      } else {
        let job = document.querySelector(".jobSelected") as HTMLDivElement;
        if (!job) return;
        let msHeight = job.parentElement.clientHeight / 86400000;
        let start = Number(job.dataset.start);
        let startTime = new Date(start);
        let end = Number(job.dataset.end);
        let endTime = new Date(end);
        startTime.setMinutes(startTime.getMinutes() + stepVal, 0, 0);
        endTime.setMinutes(endTime.getMinutes() + stepVal, 0, 0);
        let t1 = new Date(); //todo
        t1.setHours(0, 0, 0, 0);
        if (startTime < t1) {
          return;
        }
        let t2 = new Date(); //todo
        t2.setHours(23, 59, 59, 999);
        if (endTime > t2) {
          return;
        }
        job.dataset.editing = "true";
        let top = msHeight * (startTime.getTime() - t1.getTime());
        let bottom = msHeight * (t2.getTime() - endTime.getTime());
        job.style.top = `${top}px`;
        job.style.bottom = `${bottom}px`;
        job.dataset.start = startTime.getTime().toString();
        job.dataset.end = endTime.getTime().toString();
        updateTimeDom(job);
      }
    }
  };
  let onKeyUpUpdate = debounce(
    1600,
    (job: HTMLElement) => {
      delete job.dataset.editing;
      updateItem(job);
    },
    { atBegin: false }
  );

  let onKeyUp = () => {
    let job = document.querySelector("[data-editing]") as HTMLElement;
    if (!job) return;
    onKeyUpUpdate(job);
  };
  window.addEventListener("keydown", moveJobByKey);
  window.addEventListener("keyup", onKeyUp);
  eventer.on("dataReady", () => {
    getData();
  });

  return (
    <div id="ViewDay" class="view" onMouseOver={onMouseOver} onMouseOut={onMouseOut} onMouseDown={onMouseDown}>
      {[...Array(24)].map((v, i) => (
        <div class="bgLine" onMouseOver={bgLineMouseOver} onMouseOut={bgLineMouseOut}>
          <div class="hourTag">{`${i}:00`}</div>
        </div>
      ))}
    </div>
  );
}
