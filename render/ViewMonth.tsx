import { eventer } from "../common/eventer";
import { Helper } from "../common/Helper";
import ColorGet from "./ColorGet";
import { dataMonth } from "./DataMonth";
import React from "./React";
import "./ViewMonth.scss";
export default function () {
  let jobDbClick = (e: MouseEvent) => {
    let target = e.currentTarget as HTMLElement;
    let id = target.dataset.id;
    if (!id) return;
    let config = {
      title: "修改日程",
    };
    window.open(`/IndexJob.html?editId=${id}`, "_blank", JSON.stringify(config));
    Helper.$id("ModalMask").style.display = "block";
    return false;
  };
  let addJob = (e) => {
    let target = e.target as HTMLElement;
    let index = Number(target.dataset.index);
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
  eventer.on("dataReady", () => {
    let container = Helper.$id("ViewMonth").son1();
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
          cell.classAdd("notCurMonth");
        }
        //todo
        // if (dayObj.isCurDay) {
        //   cell.classAdd("selected");
        // }
        let cellContent = <div class="cellContent" data-index={index} onClick={addJob}></div>;
        dayObj.jobs.forEach((job) => {
          cellContent.appendChild(
            <div class="cellItem" data-id={job.Id} title={job.JobInfo} onMouseDown={(e) => Helper.showJobMenu(e)} onDblClick={jobDbClick} style={`--color:${ColorGet(job.ColorIndex)};`}>
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
