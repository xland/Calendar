import React from "jsx-dom";

import TitleBarBtns from "./TitleBarBtns";
import "./MainPanel.scss";
import SwitchBtns from "./SwitchBtns";
export default function () {
  
  return <div id="MainPanel">
    <div class="titleBar">
      <SwitchBtns></SwitchBtns>
      <TitleBarBtns></TitleBarBtns>
    </div>  
  </div>;
}