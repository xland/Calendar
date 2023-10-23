import React from "jsx-dom";
import "./ViewDay.scss";
export default function () {   
    let addNewJob = (e:PointerEvent)=>{
        let target = e.target as HTMLElement;
        if(target.parentElement?.getAttribute("id") != "ViewDay" && !target.classList.contains("hourTag")){
            return;
        }
        alert(1);
    }
    let getBgLineEles = ()=>{
        let eles:any[] = [];
        for(let i =0;i<24;i++){
            let ele = <div><div class="hourTag">{`${i}:00`}</div></div>
            eles.push(ele)
        }
        return eles;
    } 
  return <div id="ViewDay" onClick={addNewJob}>
    {getBgLineEles()}
  </div>;
}