import React from "jsx-dom";
import "./Job.scss";
import ColorGet from "./ColorGet";
export default function (props) {
    console.log(props.colorIndex);
    let getStyle = (alpha:number,withBorder:boolean)=>{
        if(withBorder){
            return `background: rgba(${ColorGet(props.colorIndex,alpha)});border: 1px solid rgba(${ColorGet(props.colorIndex)});`
        }else{
            return `background: rgba(${ColorGet(props.colorIndex,0)});`
        }
    }
    let onMouseOver = (e)=>{
        let target = e.target as HTMLElement;
        if(target.classList.contains("Job")){
            //@ts-ignore
            target.style = getStyle(0.2,true)
        }else{
            //@ts-ignore
            target.style = getStyle(1,false)
        }
    }
    let onMouseOut = (e)=>{
        let target = e.target as HTMLElement;
        if(target.classList.contains("Job")){
            //@ts-ignore
            target.style = getStyle(0.1,true)
        }else{
            //@ts-ignore
            target.style = getStyle(0,false)
        }
    }
  return <div class="Job"  style={getStyle(0.1,true)}  onMouseOver={onMouseOver} onMouseOut={onMouseOut} >
    <div class="dragger draggerTop"></div>
    <div class="dragger draggerBottom"></div>
  </div>;
}