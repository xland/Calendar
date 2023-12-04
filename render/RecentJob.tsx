import React from "./React";
import "./RecentJob.scss";
import { eventer } from "../common/eventer";
import { ModelJob } from "../model/ModelJob";
import { Helper } from "../common/Helper";
export default function () {
  let getStartTimeStr = (startTime: number) => {
    let span = startTime - Date.now();
    if (span < 3600000) {
      //1个小时
      let min = Math.floor(span / 60000);
      if (min < 1) {
        return `马上`;
      }
      return `${min}分钟后`;
    } else if (span < 86400000) {
      //1天
      return `${Math.floor(span / 3600000)}小时后`;
    } else {
      let startObj = new Date(startTime);
      let now = new Date();
      if (startObj.getMonth() === now.getMonth() && startObj.getFullYear() === now.getFullYear()) {
        return `${startObj.getDate() - now.getDate()}天后`;
      } else if (startObj.getFullYear() === now.getFullYear()) {
        return `${startObj.getMonth() + 1}月${startObj.getDate()}日`;
      } else {
        return `${startObj.getFullYear()}-${startObj.getMonth() + 1}-${startObj.getDate()}`;
      }
    }
  };
  let mouseDown = (e: MouseEvent) => {
    if (e.button === 0) {
      let target = e.currentTarget as HTMLElement;
      let dateObj = new Date(parseInt(target.dataset.start));
      let event = new CustomEvent("gotodateview", { detail: dateObj });
      Helper.$id("SwitchBtns").dispatchEvent(event);
      return;
    }
    Helper.showJobMenu(e);
  };
  let jobDbClick = (e: MouseEvent) => {};
  eventer.on("dataReady", async () => {
    let { ipcRenderer } = require("electron");
    let jobs: ModelJob[] = await ipcRenderer.invoke("getDataRecent");
    let dom = Helper.$id("recentJobBox");
    dom.innerHTML = "";
    for (let i = 0; i < jobs.length; i++) {
      dom.append(
        <div class="item" data-id={jobs[i].Id} data-start={jobs[i].StartTime} onMouseDown={mouseDown} onDblClick={jobDbClick}>
          <div class="title">{jobs[i].JobInfo}</div>
          <div class="time">{getStartTimeStr(jobs[i].StartTime)}</div>
        </div>
      );
    }
    let firstJob = jobs[0];
    setTimeout(() => {
      alert(123);
    }, firstJob.StartTime - Date.now());
  });

  return (
    <div id="RecentJob">
      <div id="searchBox">
        <input type="text" placeholder="搜索代办事项..." />
        <div class="searchBtn">
          <i class="iconfont icon-sousuo"></i>
        </div>
      </div>
      <div id="recentJobBox"></div>
    </div>
  );
}
