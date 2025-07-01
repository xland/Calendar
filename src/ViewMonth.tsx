import { eventer } from "./common/eventer";
import { Helper } from "./common/Helper";
import ColorGet from "./ColorGet";
import { dataMonth } from "./DataMonth";
import React from "./React";
import "./ViewMonth.scss";
export default function () {
  let addJob = async (e) => {
    let target = e.target as HTMLElement;
    let index = Number(target.dataset.index);
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
    let container = Helper.$id("ViewMonth").lastElementChild;
    container.innerHTML = "";
    let index = 0;
    for (let i = 0; i < 6; i++) {
      let row = <div class="row"></div>;
      for (let j = 0; j < 7; j++) {
        let dayObj = dataMonth.dateArr[index];
        let cell = (
          <div>
            <div class="cellHeader">{dayObj.day}</div>
          </div>
        );
        if (!dayObj.isCurMonth) {
          cell.classList.add("notCurMonth");
        }
        //todo
        // if (dayObj.isCurDay) {
        //   cell.classList.add("selected");
        // }
        let cellContent = <div class="cellContent" data-index={index} onClick={addJob}></div>;
        dayObj.jobs.forEach((job) => {
          cellContent.appendChild(
            <div class="cellItem" data-id={job.Id} title={job.JobInfo} onMouseDown={Helper.showJobMenu} onDblClick={Helper.jobDbClick} style={`--color:${ColorGet(job.ColorIndex)};`}>
              {job.JobInfo}
            </div>
          );
        });
        cell.appendChild(cellContent);
        cell.appendChild(
          <div class="addBtn" data-index={index} onClick={addJob}>
            增加
          </div>
        );
        row.appendChild(cell);
        index += 1;
      }
      container.append(row);
    }
  });

  return (
    <div id="ViewMonth" class="view">
      <div class="row header">
        <div>一</div>
        <div>二</div>
        <div>三</div>
        <div>四</div>
        <div>五</div>
        <div>六</div>
        <div>日</div>
      </div>
      <div class="content"></div>
    </div>
  );
}
