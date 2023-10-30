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
    let bgLineMouseOver = (e)=>{
        let target = e.target as HTMLElement;
        if(target.classList.contains("hourTag")) target = target.parentElement;
        target.style.background = `rgba(${ColorGet(colorIndex,0.1)})`
    }
    let bgLineMouseOut = (e)=>{
        let target = e.target as HTMLElement;
        if(target.classList.contains("hourTag")) target = target.parentElement;
        target.style.background = ``
    }
    let getBgLineEles = ()=>{
        let eles:any[] = [];
        for(let i =0;i<24;i++){
            let ele = <div onMouseOver={bgLineMouseOver} onMouseOut={bgLineMouseOut}><div class="hourTag">{`${i}:00`}</div></div>
            eles.push(ele)
        }
        return eles;
    }
    ipcRenderer.on("saveToDbOk",(e:Electron.IpcRendererEvent,data:ModelJob)=>{
        document.getElementById("ViewDay").append(<Job data={data}></Job>)
        colorIndex += 1;
        if(colorIndex > 5) colorIndex = 0; //todo
    })
    document.addEventListener("DOMContentLoaded", async ()=>{
        let data:ModelJob[] = await ipcRenderer.invoke("getJob")
        let target = document.getElementById("ViewDay");
        for(let job of data){
            target.append(<Job data={job}></Job>)
        }
        colorIndex = data[data.length-1].ColorIndex + 1;
        if(colorIndex > 5) colorIndex = 0; //todo
    })
  return <div id="ViewDay" onClick={addNewJob}> {getBgLineEles()} </div>;
}