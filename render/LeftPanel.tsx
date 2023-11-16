import React from "./React";
import "./LeftPanel.scss";
import SmallCalendar from "./SmallCalendar";
import RecentJob from "./RecentJob";
import BottomBar from "./BottomBar";
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
    <RecentJob></RecentJob>
    <BottomBar></BottomBar>
  </div>;
}