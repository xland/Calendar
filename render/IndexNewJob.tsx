import React from "jsx-dom";
import "./IndexNewJob.scss";
import WindowNewJob from "./WindowNewJob";
import TitleBarBtns from "./TitleBarBtns";
function App() {
  
  return (
    <>
      <div class="titleBar">
        <div class="title">增加日程</div>
        <TitleBarBtns></TitleBarBtns>
      </div>
      <WindowNewJob></WindowNewJob>
    </>
  );
}
document.body.appendChild(<App />);