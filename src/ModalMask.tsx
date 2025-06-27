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
  return <div id="ModalMask" onClick={maskClick}></div>;
}
