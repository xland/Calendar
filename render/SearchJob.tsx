import { Helper } from "../common/Helper";
import React from "./React";
import "./SearchJob.scss";
export default function () {
  let searchBtnClick = (e: MouseEvent) => {
    window.open(`/IndexAlert.html?id=9b0eb345-963f-4288-956d-dc6f5b399504`, "_blank", `{"title": "日程提醒" }`);
  };
  let textChange = (e: KeyboardEvent) => {
    let target = e.currentTarget as HTMLInputElement;
    if (target.value) {
      Helper.$id("SearchResult").style.display = "block";
      Helper.$id("RecentJob").style.display = "none";
    } else {
      Helper.$id("SearchResult").style.display = "none";
      Helper.$id("RecentJob").style.display = "block";
    }
  };
  return (
    <>
      <div id="SearchBox">
        <input type="text" placeholder="搜索代办事项..." onKeyUp={textChange} />
        <div class="searchBtn" onClick={searchBtnClick}>
          <i class="iconfont icon-sousuo"></i>
        </div>
      </div>
      <div id="SearchResult">123</div>
    </>
  );
}
