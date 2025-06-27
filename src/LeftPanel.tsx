import React from "./React";
import "./LeftPanel.scss";
import { eventer } from "./common/eventer";
import SmallCalendar from "./SmallCalendar";
import RecentJob from "./RecentJob";
import BottomBar from "./BottomBar";
import SearchJob from "./SearchJob";
import { Helper } from "./common/Helper";
export default function () {
  eventer.on("dataReady", async () => {
    Helper.$select("#LeftPanel > .title").addEventListener("mousedown", async () => {
      horse.win.startDrag();
    });
  });

  return (
    <div id="LeftPanel">
      <div class="title">
        <div class="icon">
          <i class="iconfont icon-calendar"></i>
        </div>
        <div class="label">日历</div>
      </div>
      <SmallCalendar></SmallCalendar>
      <SearchJob></SearchJob>
      <RecentJob></RecentJob>
      <BottomBar></BottomBar>
    </div>
  );
}
