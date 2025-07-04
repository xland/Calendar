import { Helper } from "./common/Helper";
import { ModelJob } from "./model/ModelJob";
import React from "./React";
import "./SearchJob.scss";
import { db } from "./common/db";
export default function () {
  let searchBtnClick = (e: MouseEvent) => { };
  let keyUp = async (e: KeyboardEvent) => {
    let target = e.currentTarget as HTMLInputElement;
    let dest = target.parentElement.nextElementSibling as HTMLElement;
    dest.innerHTML = "";
    if (target.value) {
      let jobs: ModelJob[] = await db.exec(`SELECT * FROM Job WHERE JobInfo like %${target.value}% order by StartTime asc`);
      for (let i = 0; i < jobs.length; i++) {
        dest.append(
          <div class="item" data-id={jobs[i].Id} data-start={jobs[i].StartTime} onMouseDown={Helper.jobItemMouseDown}>
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
        <input type="text" placeholder="搜索待办事项..." onKeyUp={keyUp} />
        <div class="searchBtn" onClick={searchBtnClick}>
          <i class="iconfont icon-search"></i>
        </div>
      </div>
      <div id="SearchResult" class="jobList"></div>
    </>
  );
}
