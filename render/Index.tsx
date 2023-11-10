// import React from "jsx-dom";
import "./Index.scss";
import LeftPanel from "./LeftPanel";
import MainPanel from "./MainPanel";
import { dataMonth } from "./DataMonth";
import React from "./React";
import { eventer } from "../event/eventer";
// import React from "jsx-dom";
let App = ()=>{
    return <><LeftPanel/><MainPanel/></>
}

// let Sub = (props)=>{
//   return <div>测试测试!!!{props.data.abc}</div>
// }

// let App = ()=>{
//   let click = ()=>{
//     alert(1);
//   }
//   return <div data-id="123" style="background:#ddd" onClick={click}>
//     <Sub data={{abc:123}}></Sub>
//     </div>
// }



document.addEventListener("DOMContentLoaded", async ()=>{
  document.body.ondragstart = () => false;
  document.body.ondragend = () => false;
  document.body.ondrop = () => false; 
  await dataMonth.init();
  document.body.appendChild(<App/>);
  eventer.emit("domReady")
})

