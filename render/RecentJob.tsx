import React from "./React";
import "./RecentJob.scss";
import { eventer } from "../common/eventer";
import { ModelJob } from "../model/ModelJob";
export default function () {
  eventer.once("dataReady", async () => {
    let { ipcRenderer } = require("electron");
    let jobs: ModelJob[] = await ipcRenderer.invoke("getDataRecent");
    let dom = document.getElementById("recentJobBox");
    for (let i = 0; i < jobs.length; i++) {
      dom.append(<div>{jobs[i].JobInfo}</div>);
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
