import React from "./React";
import "./ModalMask.scss";
export default function (props) {
  let ipcRenderer = require("electron").ipcRenderer;
  ipcRenderer.addListener("modalWindowClosed", () => {
    document.getElementById("ModalMask").style.display = "none";
  });
  let maskClick = () => {
    let ipcRenderer = require("electron").ipcRenderer;
    ipcRenderer.invoke("activeSubWindow");
  };
  return <div id="ModalMask" onClick={maskClick}></div>;
}
