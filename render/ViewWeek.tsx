import React from "./React";
import "./ViewWeek.scss";
import ColorGet from "./ColorGet";
import { ModelJob } from "../model/ModelJob";
import { eventer } from "../common/eventer";
import { dataMonth } from "./DataMonth";
export default function () {
  let addNewJob = (e) => {
    let target = e.target as HTMLElement;
    if (!target.classList.contains("column")) return;
    let day = Number(target.dataset.index) + 1;

    window.open(`/IndexJob.html?colorIndex=${colorIndex}&startTime=${startTime.getTime()}`, "_blank", JSON.stringify(config));
  };
  let jobDbClick = (e) => {};
  eventer.on("dataReady", () => {
    let container = document.getElementById("ViewWeek").lastElementChild;
    let index = dataMonth.getCurWeekFirstDayIndex();
    for (let i = 0; i < 7; i++) {
      let dayDom = <div class="column" data-index={i}></div>;
      dataMonth.dateArr[index].jobs.forEach((job) => {
        let jobEle = (
          <div class="weekJob" style={`--color:${ColorGet(job.ColorIndex)}`} onDblClick={jobDbClick}>
            {job.JobInfo}
          </div>
        );
        dayDom.append(jobEle);
      });
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
      <div class="weekContent" onClick={addNewJob}></div>
    </div>
  );
}
