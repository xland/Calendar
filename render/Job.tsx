import React from "./React";
import "./Job.scss";
export default function (props) {
  let jobDbClick = (e: MouseEvent) => {
    let target = e.target as HTMLElement;
    target = target.parentElement;
    let id = target.getAttribute("id");
    if (!id) return;
    let config = {
      winConfig: { width: 400, height: 300, title: "修改日程", minHeight: 280, minWidth: 380 },
      extraConfig: {},
    };
    window.open(`/IndexJob.html?editId=${id}`, "_blank", JSON.stringify(config));
    document.getElementById("ModalMask").style.display = "block";
  };
  let jobMouseDown = (e: MouseEvent) => {
    if (e.button != 2) return;
    let target = e.target as HTMLElement;
    target = target.parentElement;
    let menu = document.getElementById("Menu");
    let evt = new CustomEvent("show", { detail: { x: e.x, y: e.y, id: target.getAttribute("id") } });
    e.preventDefault();
    e.stopPropagation();
    menu.dispatchEvent(evt);
    return false;
  };
  return (
    <div
      class="Job"
      id={props.data.Id}
      style={props.style}
      onMouseDown={jobMouseDown}
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
