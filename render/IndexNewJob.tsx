import React from "jsx-dom";
import "./IndexNewJob.scss";
import TitleBarBtns from "./TitleBarBtns";
import {NewJobBox} from "./NewJobBox";
import ColorGet from "./ColorGet";
function App() {  
  let getStyle = (alpha = 1)=>{
    let url = new URL(window.location.href);
    let colorIndex = parseInt(url.searchParams.get("colorIndex"))
    return `background:rgba(${ColorGet(colorIndex,alpha)});`
  }
  let save = async ()=>{
    let data = NewJobBox.getData();
    let { ipcRenderer } = require("electron");
    await ipcRenderer.invoke("saveToDb","Job",data);
  }
  return (
    <>
      <div class="titleBar" style={getStyle(0.1)}>
        <div class="title">增加日程</div>
        <TitleBarBtns></TitleBarBtns>
      </div>
      <NewJobBox></NewJobBox>
      <div class="btnBox">
        <div class="btnSave" 
             style={`${getStyle()}color:#fff`} 
             //@ts-ignore
             onMouseOver={e=>e.target.style = `${getStyle(0.9)}color:#fff;`}
             //@ts-ignore
             onMouseOut={e=>e.target.style = `${getStyle()}color:#fff;`}
             onClick={save}
             >保存</div>
      </div>
    </>
  );
}
document.body.appendChild(<App />);