import React from "./React";
import "./RecentJob.scss";
import { eventer } from "../common/eventer";
import { ModelJob } from "../model/ModelJob";
import { Helper } from "../common/Helper";
export default function () {
  eventer.on("dataReady", async () => {
    let { ipcRenderer } = require("electron");
    let jobs: ModelJob[] = await ipcRenderer.invoke("getDataRecent");
    let dom = Helper.$id("RecentJob");
    dom.innerHTML = "";
    for (let i = 0; i < jobs.length; i++) {
      dom.append(
        <div class="item" data-id={jobs[i].Id} data-start={jobs[i].StartTime} onMouseDown={Helper.jobMouseDown} onDblClick={Helper.jobDbClick}>
          <div class="title">{jobs[i].JobInfo}</div>
          <div class="time">{Helper.timeStr(jobs[i].StartTime)}</div>
        </div>
      );
    }
    let firstJob = jobs[0];
    setTimeout(() => {
      alert(123);
    }, firstJob.StartTime - Date.now());
  });

  return <div id="RecentJob" class="jobList"></div>;
}
