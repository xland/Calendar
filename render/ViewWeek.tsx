import React from "./React";
import "./ViewWeek.scss";
import ColorGet from "./ColorGet";
import { eventer } from "../common/eventer";
import { dataMonth } from "./DataMonth";
import { Helper } from "../common/Helper";
export default function () {
  let addNewJob = (e) => {
    let target = e.target as HTMLElement;
    if (!target.dataset.index) {
      target = target.dad();
    }
    if (!target.dataset.index) {
      return;
    }
    let index = dataMonth.getCurWeekFirstDayIndex() + Number(target.dataset.index);
    let dateObj = dataMonth.dateArr[index];
    let colorIndex = 0;
    if (dateObj.jobs.length) {
      colorIndex = dateObj.jobs[dateObj.jobs.length - 1].ColorIndex + 1;
      if (colorIndex > 5) colorIndex = 0;
    }
    let startTime = new Date(dateObj.year, dateObj.month - 1, dateObj.day, 8, 0, 0, 0);
    let config = {
      title: "增加日程",
    };
    window.open(`/IndexJob.html?colorIndex=${colorIndex}&startTime=${startTime.getTime()}`, "_blank", JSON.stringify(config));
    Helper.$id("ModalMask").style.display = "block";
  };
  let jobDbClick = (e: MouseEvent) => {
    let id = (e.target as HTMLElement).dataset.id;
    let config = {
      title: "修改日程",
    };
    window.open(`/IndexJob.html?editId=${id}`, "_blank", JSON.stringify(config));
    Helper.$id("ModalMask").style.display = "block";
  };
  eventer.on("dataReady", () => {
    let container = Helper.$id("ViewWeek").son1();
    container.innerHTML = "";
    let index = dataMonth.getCurWeekFirstDayIndex();
    for (let i = 0; i < 7; i++) {
      let dayDom: HTMLElement = <div class="column" data-index={i}></div>;
      dataMonth.dateArr[index].jobs.forEach((job) => {
        let jobEle = (
          <div class="weekJob" title={job.JobInfo} data-id={job.Id} style={`--color:${ColorGet(job.ColorIndex)}`} onDblClick={jobDbClick} onMouseDown={(e) => Helper.showJobMenu(e)}>
            {job.JobInfo}
          </div>
        );
        dayDom.append(jobEle);
      });
      if (dayDom.children.length === 0) {
        dayDom.addEventListener("click", addNewJob);
      }
      dayDom.appendChild(
        <div class="addBtn" onClick={addNewJob}>
          增加
        </div>
      );
      container.append(dayDom);
      index += 1;
    }
  });
  return (
    <div id="ViewWeek" class="view">
      <div class="weekHeader">
        <div class="column">一</div>
        <div class="column">二</div>
        <div class="column">三</div>
        <div class="column">四</div>
        <div class="column">五</div>
        <div class="column">六</div>
        <div class="column">日</div>
      </div>
      <div class="weekContent"></div>
    </div>
  );
}
