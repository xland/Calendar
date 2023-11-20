import { eventer } from "../common/eventer";
import { dataMonth } from "./DataMonth";
import React from "./React";
import "./ViewMonth.scss";
export default function () {
  eventer.on("dataReady", () => {
    let container = document.getElementById("ViewMonth").lastElementChild;
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
        if (dayObj.isCurDay) {
          cell.classList.add("selected");
        }
        let cellContent = <div class="cellContent"></div>;
        dayObj.jobs.forEach((job) => {
          cellContent.appendChild(
            <div class="cellItem" title={job.JobInfo}>
              {job.JobInfo}
            </div>
          );
        });
        cell.appendChild(cellContent);
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
