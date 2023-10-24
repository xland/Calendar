import React, { MouseEventHandler } from "jsx-dom";
import "./ViewDay.scss";
export default function () {
    let colorIndex = 2;
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
        let config ={
            winConfig:{"width":400,"height":300,"title":"增加日程"},
            extraConfig:{}
        }
        window.open(`/IndexNewJob.html?colorIndex=${colorIndex}`,'_blank',JSON.stringify(config));
    }
    let getBgLineEles = ()=>{
        let eles:any[] = [];
        for(let i =0;i<24;i++){
            let ele = <div><div class={`halfTop color${colorIndex}`}></div>
                <div class={`halfBottom color${colorIndex}`}></div>
                <div class="hourTag">{`${i}:00`}</div></div>
            eles.push(ele)
        }
        return eles;
    } 
  return <div id="ViewDay" onClick={addNewJob}>
    {getBgLineEles()}
  </div>;
}