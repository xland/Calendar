import React from "jsx-dom";

import TitleBarBtns from "./TitleBarBtns";
import "./MainPanel.scss";
export default function () {
  return <div id="MainPanel">
    <div class="titleBar">
      <div id="switchBtns"></div>

    <TitleBarBtns></TitleBarBtns>
    </div>
  
  </div>;
}