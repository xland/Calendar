import React from "./React";
import { eventer } from "../common/eventer";
import { Helper } from "../common/Helper";
import TitleBarBtns from "./TitleBarBtns";
import "./MainPanel.scss";
import SwitchBtns from "./SwitchBtns";
import ViewDay from "./ViewDay";
import ViewWeek from "./ViewWeek";
import ViewMonth from "./ViewMonth";
export default function () {
  eventer.on("dataReady", async () => {
    Helper.$select("#SwitchBtns").addEventListener("mousedown", (e) => {
      let tar = e.target as HTMLElement
      if (tar.id === "SwitchBtns") {
        horse.win.startDrag();
      }
    });
  });
  return <div id="MainPanel">
    <div class="titleBar">
      <SwitchBtns></SwitchBtns>
      <TitleBarBtns></TitleBarBtns>
    </div>
    <ViewDay></ViewDay>
    <ViewWeek></ViewWeek>
    <ViewMonth></ViewMonth>
  </div>;
}