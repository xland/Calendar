import React from "jsx-dom";
import "./IndexNewJob.scss";
import TitleBarBtns from "./TitleBarBtns";
import NewJobBox from "./NewJobBox";
function App() {
  let url = new URL(window.location.href);
  let colorIndex = url.searchParams.get("colorIndex")
  let arr = [`3,155,229`,`106,0,255`, `96,169,2`, `87,101,2`, `216,0,115`, `216,144,0`]
  return (
    <>
      <div class="titleBar" style={`background:rgba(${arr[colorIndex]},0.1);`}>
        <div class="title">增加日程</div>
        <TitleBarBtns></TitleBarBtns>
      </div>
      <NewJobBox></NewJobBox>
      <div class="btnBox">
        <div class="btnSave" 
             style={`background:rgb(${arr[colorIndex]});color:#fff`} 
             onMouseOver={e=>e.target.style = `background:rgba(${arr[colorIndex]},0.9);color:#fff`}
             onMouseOut={e=>e.target.style = `background:rgb(${arr[colorIndex]});color:#fff`}
             >保存</div>
      </div>
    </>
  );
}
document.body.appendChild(<App />);