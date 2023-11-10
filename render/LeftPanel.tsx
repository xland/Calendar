import React from "jsx-dom";
import "./LeftPanel.scss";
import SmallCalendar from "./SmallCalendar";
export default function () {    
  return <div id="LeftPanel">
    <div class="title">
        <div class="icon">
        <i class="iconfont icon-calendar"></i>
        </div>
        <div class="label">
        日历
        </div>        
    </div>
    <SmallCalendar></SmallCalendar>
  </div>;
}