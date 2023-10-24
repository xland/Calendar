import React from "jsx-dom";
import "./NewJobBox.scss";
export default function () {   
  return <div id="NewJobBox">
<div class="timeBox">
  <div>2023</div>
  <div>-</div>
  <div>10</div>
  <div>-</div>
  <div>24</div>
  <div style="margin-left:8px">14:00</div>
  <div>-</div>
  <div>15:00</div>
</div>
<div>不重复</div>
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