import React from "jsx-dom";
import "./NewJobBox.scss";
export default function () {   
  return <div id="NewJobBox">
<div class="timeBox">
  <div>2023年</div>
  <div>10月</div>
  <div>24日</div>
  <div style="margin-left:3px">14时</div>
  <div style="margin-right:3px">15分</div>
  -
  <div style="margin-left:3px">14时</div>
  <div>15分</div>
</div>
<div>
  <div class="recycleBtn">不重复</div>
</div>
<div class="preMins">
  <div style="margin-right:3px">提前</div>
  <input type="text" value={"5"} />
  <div style="margin-left:3px">分钟提醒</div>
</div>
<div class="textareaBox">
  <textarea placeholder="事件内容"></textarea>
</div>
</div>;
}