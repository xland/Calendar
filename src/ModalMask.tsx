import React from "./React";
import "./ModalMask.scss";
import { Helper } from "./common/Helper";
export default function (props) {
  // let ipcRenderer = require("electron").ipcRenderer;
  // ipcRenderer.addListener("modalWindowClosed", () => {
  //   Helper.$id("ModalMask").style.display = "none";
  // });
  let maskClick = () => {
    // let ipcRenderer = require("electron").ipcRenderer;
    // ipcRenderer.invoke("activeSubWindow");
  };
  let loaded = (e: CustomEvent) => {
    let proxy = e.detail as Win;
    proxy.on("closing", () => {
      Helper.$id("ModalMask").style.display = "none";
      proxy.destroy();
    })
    Helper.$id("ModalMask").style.display = "block";
  }
  return <div id="ModalMask" onClick={maskClick} onLoaded={loaded}></div>;
}
