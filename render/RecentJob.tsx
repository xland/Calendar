import React from "./React";
import "./RecentJob.scss";
import { eventer } from "../common/eventer";
import { ModelJob } from "../model/ModelJob";
import { Helper } from "../common/Helper";
import { dataSetting } from "./DataSetting";
export default function () {
  let timeOutId;
  let initAlert = (id: string, startTime: number) => {
    clearTimeout(timeOutId);
    let now = Date.now();
    let beforeSpan = dataSetting.setting.AlertBefore * 60000;
    if (startTime - now - beforeSpan < 2000) {
      // window.open(`/IndexAlert.html?id=${id}`, "_blank", `{"title": "日程提醒" }`);
      // Helper.$id("ModalMask").style.display = "block";
      return false;
    }
    timeOutId = setTimeout(async () => {
      window.open(`/IndexAlert.html?id=${id}`, "_blank", `{"title": "日程提醒" }`);
      Helper.$id("ModalMask").style.display = "block";
      await initData();
    }, startTime - now - beforeSpan);
    return true;
  };
  let initData = async () => {
    let { ipcRenderer } = require("electron");
    let jobs: ModelJob[] = await ipcRenderer.invoke("getDataRecent");
    let dom = Helper.$id("RecentJob");
    dom.innerHTML = "";
    let isAlertWaiting = false;
    for (let i = 0; i < jobs.length; i++) {
      if (!isAlertWaiting) {
        isAlertWaiting = initAlert(jobs[i].Id, jobs[i].StartTime);
      }
      dom.append(
        <div class="item" data-id={jobs[i].Id} data-start={jobs[i].StartTime} onMouseDown={Helper.jobItemMouseDown}>
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
