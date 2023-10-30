import React from "jsx-dom";
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

    let func = (index:number,data:ModelJob[],useableWidth:number,start:number,end:number)=>{
        let tar = data[index]
        let sameLineJobNum = 1;
        let sameLineJobIndex = 0;
        for(let i=0;i<data.length;i++){
            if(i === index) continue;
            if(tar.StartTime < data[i].StartTime && tar.EndTime > data[i].StartTime){
                sameLineJobNum+=1
                if(i < index) sameLineJobIndex+=1;
                continue;
            }
            if(tar.StartTime < data[i].EndTime && tar.EndTime > data[i].EndTime){
                sameLineJobNum += 1
                if(i < index) sameLineJobIndex+=1;
                continue
            }
            if(tar.StartTime === data[i].StartTime && tar.EndTime === data[i].EndTime){
                sameLineJobNum += 1
                if(i < index) sameLineJobIndex+=1;
                continue
            }
        }
        let itemWidth = useableWidth / sameLineJobNum - 6; 
        let leftNum = 60+sameLineJobIndex*itemWidth+sameLineJobIndex*6
        let topNum = (tar.StartTime - start)*100/(end - start)
        let bottomNum = (end - tar.EndTime)*100/(end - start)
        let top = `top: ${topNum}%;`
        let bottom = `bottom: ${bottomNum}%;`
        let left = `left: ${leftNum}px;`
        let width = `width: ${itemWidth}px;`
        let bg = `background: rgba(${ColorGet(tar.ColorIndex,0.1)});`
        let border = `border: 1px solid rgba(${ColorGet(tar.ColorIndex)});`
        return <Job data={tar} style={`${bg}${border}${top}${bottom}${left}${width}`}></Job>
    }



    let getData = async ()=>{
        let target = document.getElementById("ViewDay");
        target.querySelectorAll(".Job").forEach(e=>e.remove())
        let useableWidth = target.clientWidth - 90;
        let data:ModelJob[] = await ipcRenderer.invoke("getJob")
        let curDay = new Date(data[0].StartTime);
        curDay.setHours(0,0,0,0);
        let start = curDay.getTime();
        curDay.setHours(23,59,59,999);
        let end = curDay.getTime();
        for(let i=0;i<data.length;i++){
            let ele = func(i,data,useableWidth,start,end)
            target.append(ele)
        }
        colorIndex = data[data.length-1].ColorIndex + 1;
        if(colorIndex > 5) colorIndex = 0;
    }
    let onMouseOver = (e)=>{
        let target = e.target as HTMLElement;
        if(target.classList.contains("dragger")){
            target.style.background = `rgba(${ColorGet(0,1)})`
        }
    }
    let onMouseOut = (e)=>{
        let target = e.target as HTMLElement;
        if(target.classList.contains("dragger")){
            target.style.background = `none`
        }
    }
    ipcRenderer.on("saveToDbOk",getData)
    document.addEventListener("DOMContentLoaded", getData)
  return <div id="ViewDay" onClick={addNewJob}  onMouseOver={onMouseOver} onMouseOut={onMouseOut}>
    {getBgLineEles()}
    </div>;
}