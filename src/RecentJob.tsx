import React from "./React";
import "./RecentJob.scss";
import { eventer } from "./common/eventer";
import { ModelJob } from "./model/ModelJob";
import { Helper } from "./common/Helper";
import { dataSetting } from "./DataSetting";
export default function () {
  let timeOutId;
  let initAlert = async (id: string, startTime: number) => {
    clearTimeout(timeOutId);
    let now = Date.now();
    let beforeSpan = dataSetting.setting.AlertBefore * 60000;
    if (startTime - now - beforeSpan < 2000) {
      let proxy = await horse.createWin({
        resizable: false,
        maximizable: false,
        minimizable: false,
        alwaysOnTop: false,
        skipTaskbar: false,
        visible: true,
        frame: false,
        shadow: true,
        title: "日程提醒",
        size: {
          w: 800,
          h: 600,
        },
        minSize: {
          w: 250,
          h: 200,
        },
        "pos": "centerScreen",
        url: `http://localhost:8000/IndexAlert.html?id=${id}`,
      });
      Helper.$id("ModalMask").style.display = "block";
      return false;
    }
    timeOutId = setTimeout(async () => {
      let proxy = await horse.createWin({
        resizable: false,
        maximizable: false,
        minimizable: false,
        alwaysOnTop: false,
        skipTaskbar: false,
        visible: true,
        frame: false,
        shadow: true,
        title: "日程提醒",
        size: {
          w: 800,
          h: 600,
        },
        minSize: {
          w: 250,
          h: 200,
        },
        "pos": "centerScreen",
        url: `http://localhost:8000/IndexAlert.html?id=${id}`,
      });
      Helper.$id("ModalMask").style.display = "block";
      await initData();
    }, startTime - now - beforeSpan);
    return true;
  };
  let initData = async () => {
    let jobs: ModelJob[] = [];
    let dom = Helper.$id("RecentJob");
    dom.innerHTML = "";
    let isAlertWaiting = false;
    for (let i = 0; i < jobs.length; i++) {
      if (!isAlertWaiting) {
        isAlertWaiting = await initAlert(jobs[i].Id, jobs[i].StartTime);
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
