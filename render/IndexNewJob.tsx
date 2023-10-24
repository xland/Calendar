import React from "jsx-dom";
import "./IndexNewJob.scss";
import WindowNewJob from "./WindowNewJob";
import TitleBarBtns from "./TitleBarBtns";
function App() {
  let url = new URL(window.location.href);
  let colorIndex = url.searchParams.get("colorIndex")
  console.log(colorIndex)
  return (
    <>
      <div class={`titleBar color${colorIndex}`}>
        <div class="title">增加日程</div>
        <TitleBarBtns></TitleBarBtns>
      </div>
      <WindowNewJob></WindowNewJob>
    </>
  );
}
document.body.appendChild(<App />);