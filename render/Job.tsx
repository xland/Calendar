import React from "jsx-dom";
import "./Job.scss";
export default function (props) {
  return <div class="Job" style={props.style}>
    <div class="dragger draggerTop"></div>
    <div class="dragger draggerBottom"></div>
    {props.data.JobInfo}
  </div>;
}