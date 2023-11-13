import "./Index.scss";
import LeftPanel from "./LeftPanel";
import MainPanel from "./MainPanel";
import { dataMonth } from "./DataMonth";
import React from "./React";
// import React from "jsx-dom";
let App = ()=>{
    return <><LeftPanel/><MainPanel/></>
}



document.addEventListener("DOMContentLoaded", ()=>{
  document.body.ondragstart = () => false;
  document.body.ondragend = () => false;
  document.body.ondrop = () => false; 
  document.body.appendChild(<App/>);
  dataMonth.init();
})

