import React from "./React";
import "./ViewWeek.scss";
import ColorGet from "./ColorGet";
import { ModelJob } from "../model/ModelJob";
import { eventer } from "../event/eventer";
import { dataMonth } from "./DataMonth";
export default function () {
    let addNewJob = (e)=>{
        let target = e.target as HTMLElement
        if(!target.classList.contains("column")) return;
        window.open(`/IndexNewJob.html?colorIndex=${colorIndex}&startTime=${startTime.getTime()}`,'_blank',JSON.stringify(config));
    }
    eventer.once("domReady",()=>{
        let container = document.getElementById("ViewWeek").lastElementChild;
        let items = dataMonth.getCurWeek();
        for(let i=0;i<items.length;i++){
            let dayDom = <div class="column"></div>
            for (let index = 0;index < items[i].length; index++) {
                const jobEle = <div class="weekJob" style={`--color:${ColorGet(items[i][index].ColorIndex)}`}>{items[i][index].JobInfo}</div>;
                dayDom.append(jobEle);
            }
            container.append(dayDom)
        }
    })
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