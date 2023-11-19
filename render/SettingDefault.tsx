import React from "./React";
import "./SettingDefault.scss";
export default function (props) {
  let allen = () => {};
  return (
    <div id="settingDefault">
      <div onClick={allen} class="settingRow">
        <div>
          <i class="iconfont icon-uncheck"></i>
        </div>
        <div>开机自启动</div>
      </div>
      <div class="settingRow">
        <div>
          <i class="iconfont icon-uncheck"></i>
        </div>
        <div>显示农历</div>
      </div>
      <div class="settingRow">
        <div>
          <i class="iconfont icon-uncheck"></i>
        </div>
        <div>压缩数据库</div>
      </div>
    </div>
  );
}
