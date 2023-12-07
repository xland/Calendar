import React from "./React";
import "./Job.scss";
import { Helper } from "../common/Helper";
export default function (props) {
  return (
    <div
      class="Job"
      data-id={props.data.Id}
      style={props.style}
      onMouseDown={Helper.showJobMenu}
      onDblClick={Helper.jobDbClick}
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
