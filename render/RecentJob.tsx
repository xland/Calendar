import React from "./React";
import "./RecentJob.scss";
import { eventer } from "../common/eventer";
import { ModelJob } from "../model/ModelJob";
export default function () {
  eventer.once("dataReady", async () => {
    let { ipcRenderer } = require("electron");
    let jobs: ModelJob[] = await ipcRenderer.invoke("getDataRecent");
    let dom = document.getElementById("recentJobBox");
    let getStartTimeStr = (startTime: number) => {
      let span = startTime - Date.now();
      if (span < 3600000) {
        //1个小时
        return `${Math.floor(span / 3600000)}分钟后`;
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
    for (let i = 0; i < jobs.length; i++) {
      dom.append(
        <div class="item">
          <div class="title">{jobs[i].JobInfo}</div>
          <div class="time">{getStartTimeStr(jobs[i].StartTime)}</div>
        </div>
      );
    }
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
