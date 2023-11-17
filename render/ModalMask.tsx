import React from "./React";
import "./ModalMask.scss"
export default function (props) { 
  let ipcRenderer = require("electron").ipcRenderer
  ipcRenderer.addListener("modalWindowClosed",()=>{
    document.getElementById("ModalMask").style.display = "none"
  })
  return <div id="ModalMask"></div>;
}