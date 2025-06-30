import React from "./React";
import { Helper } from "./common/Helper";
import { eventer } from "./common/eventer";
import "./TitleBarBtns.scss";
export default function () {
  let minimize = () => {
    horse.win.minimize();
  };
  let restore = () => {
    horse.win.restore();
  };
  let maximize = () => {
    horse.win.maximize();
  };
  let close = () => {
    horse.win.close();
  };
  eventer.on("dataReady", () => {
    horse.win.on("stateChanged", (result) => {
      if (result.state == "maximize") {
        Helper.$id("maximizeBtn").style.display = "none";
        Helper.$id("restoreBtn").style.display = "";
      } else if (result.state == "restore") {
        Helper.$id("maximizeBtn").style.display = "";
        Helper.$id("restoreBtn").style.display = "none";
      }
    });
  });
  return (
    <div id="TitleBarBtns">
      <div onClick={minimize}>
        <i class="iconfont icon-minimize"></i>
      </div>
      <div onClick={restore} id="restoreBtn" style="display: none;">
        <i class="iconfont icon-restore"></i>
      </div>
      <div onClick={maximize} id="maximizeBtn">
        <i class="iconfont icon-maximize"></i>
      </div>
      <div onClick={close} id="closeBtn">
        <i class="iconfont icon-close"></i>
      </div>
    </div>
  );
}
