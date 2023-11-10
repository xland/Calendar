import React from "./React";
import "./ViewWeek.scss";
import ColorGet from "./ColorGet";
import { ipcRenderer } from "electron";
import { ModelJob } from "../model/ModelJob";
export default function () {
    let addNewJob = (e)=>{
        let target = e.target as HTMLElement
        if(!target.classList.contains("column")) return;
        window.open(`/IndexNewJob.html?colorIndex=${colorIndex}&startTime=${startTime.getTime()}`,'_blank',JSON.stringify(config));
    }
    let getData = async ()=>{
        let t = new Date();
        t.setDate(t.getDate()-(t.getDay()-1))
        t.setHours(0,0,0,0);
        let start = t.getTime();
        t.setDate(t.getDate()+6)
        t.setHours(23,59,59,999)
        let end = t.getTime()
        let sql = `SELECT * FROM Job WHERE StartTime >= ? and EndTime <= ? order by StartTime asc`
        let items:ModelJob[] = await ipcRenderer.invoke("getData",sql,start,end)
        let result:ModelJob[][] = [[],[],[],[],[],[],[]]
        let dayLastTime = new Date(start);
        dayLastTime.setHours(23,59,59,999)
        let index = 0;
        for(let i=0;i<items.length;i++){
            if(items[i].EndTime < dayLastTime.getTime()){
                result[index].push(items[i])
            }else{
                index+=1;
                dayLastTime.setDate(dayLastTime.getDate()+1)
                console.log(dayLastTime);
                result[index].push(items[i])
            }
        }
        return result
    }
    let getDataDom = async ()=>{
        let items = await getData();
        let container = document.getElementById("ViewWeek").lastElementChild;
        for(let i=0;i<items.length;i++){
            let dayDom = <div class="column"></div>
            for (let index = 0;index < items[i].length; index++) {
                const jobEle = <div class="weekJob" style={`--color:${ColorGet(items[i][index].ColorIndex)}`}>{items[i][index].JobInfo}</div>;
                dayDom.append(jobEle);
            }
            container.append(dayDom)
        }
    }
    // document.addEventListener("DOMContentLoaded", async ()=>{
    //     await getDataDom();
    // })
    return <div id="ViewWeek" class="view" style="z-index:20;">
        <div class="weekHeader">
            <div class="column">一</div>
            <div class="column">二</div>
            <div class="column">三</div>
            <div class="column">四</div>
            <div class="column">五</div>
            <div class="column">六</div>
            <div class="column">日</div>
        </div>
        <div class="weekContent" onClick={addNewJob}>
            
        </div>
    </div>
}