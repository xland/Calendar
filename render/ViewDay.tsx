import React, { MouseEventHandler } from "jsx-dom";
import "./ViewDay.scss";
import Job from "./Job";
import ColorGet from "./ColorGet";
import { ipcRenderer } from "electron";
import { ModelJob } from "../model/ModelJob";
export default function () {
    let colorIndex = 0;
    let addNewJob = (e:any)=>{
        let target = e.target as HTMLElement;
        let startHour:string;
        if(target.classList.contains("hourTag")){
            startHour = target.innerHTML;
        }else if(target.firstElementChild.classList.contains("hourTag")){
            startHour = target.firstElementChild.innerHTML;
        }
        if(!startHour) return;
        let hour = parseInt(startHour.split(":")[0]);
        let startTime = new Date();
        startTime.setHours(hour);
        let config ={
            winConfig:{width:400,height:300,title:"增加日程",minHeight:280,minWidth:380},
            extraConfig:{}
        }
        window.open(`/IndexNewJob.html?colorIndex=${colorIndex}&startTime=${startTime.getTime()}`,'_blank',JSON.stringify(config));
    }
    let getBgLineEles = ()=>{
        let eles:any[] = [];
        for(let i =0;i<24;i++){
            let ele = <div 
            //@ts-ignore
            onMouseOver={e=>e.target.style = `background:rgba(${ColorGet(colorIndex,0.1)});`}
            //@ts-ignore
            onMouseOut={e=>e.target.style = `background:rgba(0,0,0,0);`}
            ><div class="hourTag">{`${i}:00`}</div></div>
            eles.push(ele)
        }
        return eles;
    }
    ipcRenderer.on("saveToDbOk",(e:Electron.IpcRendererEvent,data:ModelJob)=>{
        document.getElementById("ViewDay").append(<Job colorIndex={colorIndex}></Job>)
        colorIndex += 1;
        if(colorIndex > 5) colorIndex = 0;
    })
  return <div id="ViewDay" onClick={addNewJob}> {getBgLineEles()} </div>;
}