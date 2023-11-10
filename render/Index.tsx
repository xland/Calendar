// import React from "jsx-dom";
import "./Index.scss";
import LeftPanel from "./LeftPanel";
import MainPanel from "./MainPanel";
import { dataMonth } from "./DataMonth";
import React from "./React";
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

document.body.appendChild(<App/>);

document.addEventListener("DOMContentLoaded", async ()=>{
  document.body.ondragstart = () => false;
  document.body.ondragend = () => false;
  document.body.ondrop = () => false;
  await dataMonth.init(); //这个比子控件晚，如果早的话，子控件就没办法注册DOMContentLoaded
  
  // App.ready()
})

