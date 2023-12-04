import React from "./React";
import "./Job.scss";
import { Helper } from "../common/Helper";
export default function (props) {
  let jobDbClick = (e: MouseEvent) => {
    let target = e.currentTarget as HTMLElement;
    let id = target.dataset.id;
    if (!id) return;
    let config = {
      winConfig: { width: 480, height: 380, title: "修改日程", minHeight: 380, minWidth: 480 },
      extraConfig: {},
    };
    window.open(`/IndexJob.html?editId=${id}`, "_blank", JSON.stringify(config));
    Helper.$id("ModalMask").style.display = "block";
  };
  return (
    <div
      class="Job"
      data-id={props.data.Id}
      style={props.style}
      onMouseDown={(e) => Helper.showJobMenu(e)}
      onDblClick={jobDbClick}
      data-text={props.data.JobInfo}
      data-start={props.data.StartTime}
      data-end={props.data.EndTime}
    >
      <div class="dragger draggerTop"></div>
      <div class="dragger draggerBottom"></div>
      <div class="time timeTop"></div>
      <div class="time timeBottom"></div>
      <div class="jobInfo">{props.data.JobInfo}</div>
    </div>
  );
}
