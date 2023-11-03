import React from "jsx-dom";
import "./ViewWeek.scss";
export default function () {
    document.addEventListener("DOMContentLoaded", ()=>{
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
        <div class="weekContent">
            <div class="column"></div>
            <div class="column"></div>
            <div class="column"></div>
            <div class="column"></div>
            <div class="column"></div>
            <div class="column"></div>
            <div class="column"></div>
        </div>
    </div>
}