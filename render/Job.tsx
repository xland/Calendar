import React from "jsx-dom";
import "./Job.scss";
import ColorGet from "./ColorGet";
import { ModelJob } from "../model/ModelJob";
export default function (props) {
    let data = props.data as ModelJob
    let onMouseOver = (e)=>{
        let target = e.target as HTMLElement;
        if(target.classList.contains("Job")){
            target.style.background = `rgba(${ColorGet(data.ColorIndex,0.2)})`
            target.style.border = `1px solid rgba(${ColorGet(data.ColorIndex,0.8)})`
        }else{
            target.style.background = `rgba(${ColorGet(data.ColorIndex,1)})`
        }
    }
    let onMouseOut = (e)=>{
        let target = e.target as HTMLElement;
        if(target.classList.contains("Job")){
            target.style.background = `rgba(${ColorGet(data.ColorIndex,0.1)})`
            target.style.border = `1px solid rgba(${ColorGet(data.ColorIndex)})`
        }else{
            target.style.background = `none`
        }
    }
    let getStyle = ()=>{
        let curDay = new Date(data.StartTime);
        curDay.setHours(0,0,0,0);
        let start = curDay.getTime();
        curDay.setHours(23,59,59,999);
        let end = curDay.getTime();
        let topNum = (data.StartTime - start)*100/(end - start)
        let bottomNum = (end - data.EndTime)*100/(end - start)
        let top = `top: ${topNum}%;`
        let bottom = `bottom: ${bottomNum}%;`
        let bg = `background: rgba(${ColorGet(data.ColorIndex,0.1)});`
        let border = `border: 1px solid rgba(${ColorGet(data.ColorIndex)});`
        return `${bg}${border}${top}${bottom}`;
    }
  return <div class="Job"  style={getStyle()} onMouseOver={onMouseOver} onMouseOut={onMouseOut} >
    <div class="dragger draggerTop"></div>
    <div class="dragger draggerBottom"></div>
  </div>;
}