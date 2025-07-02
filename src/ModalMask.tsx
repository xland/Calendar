import React from "./React";
import "./ModalMask.scss";
import { Helper } from "./common/Helper";
import { eventer } from "./common/eventer";
export default function (props) {
  let tarId: number
  let maskClick = async () => {
    debugger;
    await horse.win.sendMsg(tarId, "flashAndActivate");
  };
  let loaded = (e: CustomEvent) => {
    tarId = e.detail as number
    Helper.$id("ModalMask").style.display = "block";
  }
  eventer.on("dataReady", () => {
    horse.win.on("msg", (msg) => {
      if (msg.data === "close") {
        Helper.$id("ModalMask").style.display = "none";
      }
    })
  })
  return <div id="ModalMask" onClick={maskClick} onLoaded={loaded}></div>;
}
