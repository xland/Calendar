import React from "jsx-dom";
import "./ViewDay.scss";
export default function () {   
    let getBgLineEles = ()=>{
        let eles:any[] = [];
        for(let i =0;i<24;i++){
            let ele = <div><div class="hourTag">{`${i}:00`}</div></div>
            eles.push(ele)
        }
        return eles;
    } 
  return <div id="ViewDay">
    {getBgLineEles()}
  </div>;
}