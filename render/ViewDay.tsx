import React from "jsx-dom";
import "./ViewDay.scss";
import Job from "./Job";
import ColorGet from "./ColorGet";
import { ipcRenderer } from "electron";
import { ModelJob } from "../model/ModelJob";
export default function () {
    let colorIndex = 0;
    let addNewJob = (target:HTMLElement)=>{
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
        target.style.background = `rgba(${ColorGet(colorIndex)},0.1)`
    }
    let bgLineMouseOut = (e)=>{
        let target = e.target as HTMLElement;
        if(target.classList.contains("hourTag")) target = target.parentElement;
        target.style.background = ``
    }
    let getBgLineEles = ()=>{
        let eles:any[] = [];
        for(let i =0;i<24;i++){
            let ele = <div class="bgLine" onMouseOver={bgLineMouseOver} onMouseOut={bgLineMouseOut}><div class="hourTag">{`${i}:00`}</div></div>
            eles.push(ele)
        }
        return eles;
    }
    let styleItem = (index:number,data:ModelJob[],useableWidth:number,start:number,end:number)=>{
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
        let styleObj = {top:`${topNum}%`,bottom:`${bottomNum}%`,left:leftNum,width:itemWidth,'--color':ColorGet(tar.ColorIndex)};
        return <Job data={tar} style={styleObj}></Job>
    }
    let getData = async ()=>{
        let now = new Date();
        now.setHours(0,0,0,0);
        let start = now.getTime();
        now.setHours(23,59,59,999);
        let end = now.getTime();
        let data:ModelJob[] = await ipcRenderer.invoke("getData","SELECT * FROM Job WHERE StartTime >= ? and EndTime <= ? order by StartTime asc",start,end)
        if(data.length < 1) return;
        let target = document.getElementById("ViewDay");
        target.querySelectorAll(".Job").forEach(e=>e.remove())
        let useableWidth = target.clientWidth - 90;
        
        for(let i=0;i<data.length;i++){
            let ele = styleItem(i,data,useableWidth,start,end)
            target.append(ele)
        }
        colorIndex = data[data.length-1].ColorIndex + 1;
        if(colorIndex > 5) colorIndex = 0;
    }
    let getChangedTime = (target:HTMLElement)=>{
        let height = target.parentElement.clientHeight;
        let ms = target.offsetTop/height*86400000
        let now = new Date();
        now.setHours(0,0,0,0);
        now.setMilliseconds(ms);
        let StartTime = now.getTime();
        now.setHours(0,0,0,0);
        ms = (target.offsetTop + target.clientHeight)/height*86400000
        now.setMilliseconds(ms);
        let EndTime = now.getTime();
        return {StartTime,EndTime}
        console.log(new Date(StartTime),new Date(EndTime));
    }
    let updateTimeDom = (target:HTMLElement)=>{
        let {StartTime,EndTime} = getChangedTime(target);
        let timeDiv = target.querySelector(".timeTop") as HTMLDivElement;
        let dt = new Date(StartTime);
        let minutes = dt.getMinutes();
        if(dt.getSeconds()>0 || dt.getMilliseconds()>0){
            minutes+=1;
            console.log("start")
        }
        timeDiv.innerHTML = `${dt.getHours().toString().padStart(2,"0")}:${minutes.toString().padStart(2,"0")}`;
        timeDiv = target.querySelector(".timeBottom") as HTMLDivElement;
        dt = new Date(EndTime);
        minutes = dt.getMinutes();
        if(dt.getSeconds()>0 || dt.getMilliseconds()>0){
            minutes+=1;
            console.log("end")
        }
        timeDiv.innerHTML = `${dt.getHours().toString().padStart(2,"0")}:${minutes.toString().padStart(2,"0")}`;
    }
    let onMouseOver = (e)=>{
        let target = e.target as HTMLElement;
        if(target.classList.contains("dragger")){            
            target.style.background = `rgb(var(--color))`
        }
    }
    let onMouseOut = (e)=>{
        let target = e.target as HTMLElement;
        if(target.classList.contains("dragger")){
            target.style.background = `none`
        }
    }
    let onMouseDown = (e:MouseEvent)=>{
        let target = e.target as HTMLElement;
        if(target.classList.contains("bgLine")){
            addNewJob(target);
            return;
        }else if(target.classList.contains("dragger")){
            document.querySelectorAll(".jobSelected").forEach(v=>v.classList.remove("jobSelected"))
            target.parentElement.classList.add("jobSelected")
            if(target.classList.contains("draggerSelected")){
                target.classList.remove("draggerSelected")
            }else{
                document.querySelectorAll(".draggerSelected").forEach(v=>v.classList.remove("draggerSelected"))            
                target.classList.add("draggerSelected")
            }
        }else if(target.classList.contains("Job")){
            document.querySelectorAll(".jobSelected").forEach(v=>v.classList.remove("jobSelected"))
            document.querySelectorAll(".draggerSelected").forEach(v=>v.classList.remove("draggerSelected"))
            target.classList.add("jobSelected")
        }else {
            return;
        }
        if(!target.classList.contains("dragger") && !target.classList.contains("Job")) return;
        let oldY = e.y;
        let oldHeight = target.clientHeight;
        let documentMouseMove = (e) => {
            if(target.classList.contains("draggerTop")){
                target.style.background = target.parentElement.style.borderColor
                target.parentElement.parentElement.style.cursor = "ns-resize";
                let top = e.y - target.parentElement.parentElement.offsetTop;
                if(top < 0) top = 0;
                target.parentElement.style.top = top + "px";
                updateTimeDom(target.parentElement);
            }else if(target.classList.contains("draggerBottom")){
                target.style.background = target.parentElement.style.borderColor
                target.parentElement.parentElement.style.cursor = "ns-resize";
                let bottom = target.parentElement.parentElement.clientHeight + target.parentElement.parentElement.offsetTop - e.y;
                if(bottom < 0) bottom = 0;
                target.parentElement.style.bottom = bottom + "px";
                updateTimeDom(target.parentElement);
            }else if(target.classList.contains("Job")) {
                let span = e.y - oldY;
                let top = target.offsetTop + span;
                oldY = e.y
                if(top < 0  || top + oldHeight > target.parentElement.clientHeight) return;
                target.style.top = top + "px";
                let bottom = target.parentElement.clientHeight - oldHeight - target.offsetTop-1;
                target.style.bottom = bottom + "px";
                updateTimeDom(target);
                console.log(oldHeight)
            }         
        };
        let documentMouseUp = (e) => {
            document.removeEventListener("mousemove", documentMouseMove);
            document.removeEventListener("mouseup", documentMouseUp);
            let id;
            if(target.classList.contains("dragger")){
                target.style.background = `none`
                target.parentElement.parentElement.style.cursor = "pointer";
                id = target.parentElement.getAttribute("id");
            }else{
                id = target.getAttribute("id")
            }
            target = null;
            // updateItem(id)
            //todo saveData
        };
        document.addEventListener("mousemove", documentMouseMove);
        document.addEventListener("mouseup", documentMouseUp);
        e.preventDefault();
        return false;
    }
    ipcRenderer.on("saveToDbOk",getData)
    document.addEventListener("DOMContentLoaded", ()=>{
        getData();
        window.addEventListener("keydown",(e:KeyboardEvent)=>{
            console.log(e.key)
            if(e.key === "ArrowUp"){

            }else if(e.key === "Escape"){
                document.querySelectorAll(".draggerSelected").forEach(v=>v.classList.remove("draggerSelected"))
                document.querySelectorAll(".jobSelected").forEach(v=>v.classList.remove("jobSelected"))
            }
        })
    })
  return <div id="ViewDay" onMouseOver={onMouseOver} onMouseOut={onMouseOut} onMouseDown={onMouseDown}>
    {getBgLineEles()}
    </div>;
}