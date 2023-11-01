import React from "jsx-dom";
import "./Job.scss";
export default function (props) {
  return <div class="Job" id={props.data.Id} style={props.style}>
    <div class="dragger draggerTop"></div>
    <div class="dragger draggerBottom"></div>
    <div class="time timeTop"></div>
    <div class="time timeBottom"></div>
    {props.data.JobInfo}
  </div>;
}