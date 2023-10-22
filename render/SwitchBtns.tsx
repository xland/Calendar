import React from "jsx-dom";
import "./SwitchBtns.scss";
export default function () {
  return <div id="SwitchBtns">
    <div class="btns navigateBtns">
        <div class="selected">日</div>
        <div>周</div>
        <div>月</div>
    </div>
    <div class="btns dayBtns">
        <div>
            <i class="iconfont icon-zuojiantou"></i>
        </div>
        <div>2011-11-11</div>
        <div>
            <i class="iconfont icon-youjiantou"></i>
        </div>
    </div>
  </div>;
}