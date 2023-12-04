import { eventer } from "../common/eventer";
import { Helper } from "../common/Helper";
import ColorGet from "./ColorGet";
import { dataMonth } from "./DataMonth";
import React from "./React";
import "./ViewMonth.scss";
export default function () {
  let jobDbClick = (e) => {
    let target = e.target as HTMLElement;
    let id = target.getAttribute("id");
    if (!id) return;
    let config = {
      winConfig: { width: 480, height: 380, title: "修改日程", minHeight: 380, minWidth: 480 },
      extraConfig: {},
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
      winConfig: { width: 480, height: 380, title: "增加日程", minHeight: 380, minWidth: 480 },
      extraConfig: {},
    };
    window.open(`/IndexJob.html?colorIndex=${colorIndex}&startTime=${startTime.getTime()}`, "_blank", JSON.stringify(config));
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
            <div class="cellItem" id={job.Id} title={job.JobInfo} onDblClick={jobDbClick} style={`--color:${ColorGet(job.ColorIndex)};`}>
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
