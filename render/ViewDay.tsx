import React, { MouseEventHandler } from "jsx-dom";
import "./ViewDay.scss";
import Job from "./Job";
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
        let newIndex = colorIndex + 1;
        if(newIndex > 5){
            newIndex = 0;
        }
        let eleArr = document.querySelectorAll(".color"+colorIndex);
        eleArr.forEach(ele=>{
            ele.classList.remove("color"+colorIndex);
            ele.classList.add("color"+newIndex);
        })
        colorIndex = newIndex;
    }
    let getBgLineEles = ()=>{
        let eles:any[] = [];
        for(let i =0;i<24;i++){
            let ele = <div class={`color${colorIndex}`}><div class="hourTag">{`${i}:00`}</div></div>
            eles.push(ele)
        }
        return eles;
    } 
    let getJobs = ()=>{        
        return <Job></Job>
    }
  return <div id="ViewDay" onClick={addNewJob}>
    {getBgLineEles()}
    {getJobs()}
  </div>;
}