import React from "./React";
import "./RecentJob.scss";
import { eventer } from "../common/eventer";
import { ModelJob } from "../model/ModelJob";
import { Helper } from "../common/Helper";
export default function () {
  let timeOutId;
  let initAlert = (id: string, startTime: number) => {
    timeOutId = setTimeout(async () => {
      window.open(`/IndexAlert.html?id=${id}`, "_blank", `{"title": "日程提醒" }`);
      Helper.$id("ModalMask").style.display = "block";
      await initData();
    }, startTime - Date.now() + 1);
  };
  let initData = async () => {
    clearTimeout(timeOutId);
    let { ipcRenderer } = require("electron");
    let jobs: ModelJob[] = await ipcRenderer.invoke("getDataRecent");
    let dom = Helper.$id("RecentJob");
    dom.innerHTML = "";
    for (let i = 0; i < jobs.length; i++) {
      if (i === 0) {
        initAlert(jobs[i].Id, jobs[i].StartTime);
      }
      dom.append(
        <div class="item" data-id={jobs[i].Id} data-start={jobs[i].StartTime} onMouseDown={Helper.jobMouseDown} onDblClick={Helper.jobDbClick}>
          <div class="title">{jobs[i].JobInfo}</div>
          <div class="time">{Helper.timeStr(jobs[i].StartTime)}</div>
        </div>
      );
    }
  };
  eventer.on("dataReady", async () => {
    await initData();
  });

  return <div id="RecentJob" class="jobList"></div>;
}
