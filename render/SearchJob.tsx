import { Helper } from "../common/Helper";
import { ModelJob } from "../model/ModelJob";
import React from "./React";
import "./SearchJob.scss";
export default function () {
  let searchBtnClick = (e: MouseEvent) => {
    window.open(`/IndexAlert.html?id=9b0eb345-963f-4288-956d-dc6f5b399504`, "_blank", `{"title": "日程提醒" }`);
  };
  let keyUp = async (e: KeyboardEvent) => {
    let target = e.currentTarget as HTMLInputElement;
    let dest = target.dad().next();
    dest.innerHTML = "";
    if (target.value) {
      let { ipcRenderer } = require("electron");
      let jobs: ModelJob[] = await ipcRenderer.invoke("getData", "SELECT * FROM Job WHERE JobInfo like ? order by StartTime asc", `%${target.value}%`);
      for (let i = 0; i < jobs.length; i++) {
        dest.append(
          <div class="item" data-id={jobs[i].Id} data-start={jobs[i].StartTime} onMouseDown={Helper.jobMouseDown} onDblClick={Helper.jobDbClick}>
            <div class="title">{jobs[i].JobInfo}</div>
            <div class="time">{Helper.timeStr(jobs[i].StartTime)}</div>
          </div>
        );
      }
      dest.style.display = "block";
      Helper.$id("RecentJob").style.display = "none";
    } else {
      dest.style.display = "none";
      Helper.$id("RecentJob").style.display = "block";
    }
  };
  return (
    <>
      <div id="SearchBox">
        <input type="text" placeholder="搜索代办事项..." onKeyUp={keyUp} />
        <div class="searchBtn" onClick={searchBtnClick}>
          <i class="iconfont icon-sousuo"></i>
        </div>
      </div>
      <div id="SearchResult" class="jobList"></div>
    </>
  );
}
