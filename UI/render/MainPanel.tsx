import React from "./React";
import TitleBarBtns from "./TitleBarBtns";
import "./MainPanel.scss";
import SwitchBtns from "./SwitchBtns";
import ViewDay from "./ViewDay";
import ViewWeek from "./ViewWeek";
import ViewMonth from "./ViewMonth";
export default function () {  
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