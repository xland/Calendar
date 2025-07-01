import React from "./React";
import "./ViewWeek.scss";
import ColorGet from "./ColorGet";
import { eventer } from "./common/eventer";
import { dataMonth } from "./DataMonth";
import { Helper } from "./common/Helper";
export default function () {
  let addNewJob = async (e) => {
    let target = e.target as HTMLElement;
    if (!target.dataset.index) {
      target = target.parentElement;
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
    let proxy = await horse.createWin({
      resizable: false,
      maximizable: false,
      minimizable: false,
      alwaysOnTop: false,
      skipTaskbar: false,
      visible: true,
      frame: false,
      shadow: true,
      title: "增加日程",
      size: {
        w: 800,
        h: 600,
      },
      minSize: {
        w: 250,
        h: 200,
      },
      "pos": "centerScreen",
      url: `http://localhost:8000/IndexJob.html?colorIndex=${colorIndex}&startTime=${startTime.getTime()}`,
    });


    Helper.$id("ModalMask").style.display = "block";
  };
  eventer.on("dataReady", () => {
    let container = Helper.$id("ViewWeek").lastElementChild;
    container.innerHTML = "";
    let index = dataMonth.getCurWeekFirstDayIndex();
    for (let i = 0; i < 7; i++) {
      let dayDom: HTMLElement = <div class="column" data-index={i}></div>;
      dataMonth.dateArr[index].jobs.forEach((job) => {
        let jobEle = (
          <div class="weekJob" title={job.JobInfo} data-id={job.Id} style={`--color:${ColorGet(job.ColorIndex)}`} onDblClick={Helper.jobDbClick} onMouseDown={Helper.showJobMenu}>
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
