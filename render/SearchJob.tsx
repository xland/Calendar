import React from "./React";
import "./SearchJob.scss";
export default function () {
  let searchBtnClick = (e: MouseEvent) => {
    window.open(`/IndexAlert.html?id=9b0eb345-963f-4288-956d-dc6f5b399504`, "_blank", `{"title": "日程提醒" }`);
  };
  return (
    <div id="SearchJob">
      <input type="text" placeholder="搜索代办事项..." />
      <div class="searchBtn" onClick={searchBtnClick}>
        <i class="iconfont icon-sousuo"></i>
      </div>
    </div>
  );
}
