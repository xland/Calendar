import React from "./React";
import "./Job.scss";
export default function (props) {
  let jobDbClick = (e) => {
    let config = {
      winConfig: { width: 400, height: 300, title: "修改日程", minHeight: 280, minWidth: 380 },
      extraConfig: {},
    };
    window.open(`/IndexJob.html?editId=${props.data.Id}`, "_blank", JSON.stringify(config));
  };
  return (
    <div class="Job" id={props.data.Id} style={props.style} onDblClick={jobDbClick} data-text={props.data.JobInfo} data-start={props.data.StartTime} data-end={props.data.EndTime}>
      <div class="dragger draggerTop"></div>
      <div class="dragger draggerBottom"></div>
      <div class="time timeTop"></div>
      <div class="time timeBottom"></div>
      <div class="jobInfo">{props.data.JobInfo}</div>
    </div>
  );
}
