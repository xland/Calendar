import React, { MouseEventHandler } from "jsx-dom";
import "./ViewDay.scss";
export default function () {   
    let addNewJob = (e:any)=>{
        let target = e.target as HTMLElement;
        let timeEle;
        if(target.classList.contains("halfTop")){
            timeEle = target.nextElementSibling.nextElementSibling;
        }else if(target.classList.contains("halfBottom")){
            timeEle = target.nextElementSibling;
        }else if(target.classList.contains("hourTag")){
            timeEle = target;
        }
        if(!timeEle) return;
        window.open("/IndexNewJob.html");
    }
    let getBgLineEles = ()=>{
        let eles:any[] = [];
        for(let i =0;i<24;i++){
            let ele = <div><div class="halfTop half0"></div>
                <div class="halfBottom half0"></div>
                <div class="hourTag">{`${i}:00`}</div></div>
            eles.push(ele)
        }
        return eles;
    } 
  return <div id="ViewDay" onClick={addNewJob}>
    {getBgLineEles()}
  </div>;
}