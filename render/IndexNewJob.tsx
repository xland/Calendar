import React from "jsx-dom";
import "./IndexNewJob.scss";
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
      <div class="eventBox">
        <div>
          <textarea placeholder="事件内容（Enter换行）"></textarea>
        </div>
        <div>
          2023-10-24 14:00-15:00
        </div>
        <div>不重复</div>
        <div>提前
          <input type="text" value={"5"} />分钟提醒
        </div>
      </div>
      <div class="btnBox">
        <button>保存</button>
      </div>
    </>
  );
}
document.body.appendChild(<App />);