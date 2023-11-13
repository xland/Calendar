import React from "./React"
import "./RecentJob.scss"
export default function(){
    let searchBoxFocus = (e)=>{
        let target = e.target as HTMLInputElement
        target.parentElement.style.borderBottom = "1px solid #f02c38"
    }
    let searchBoxBlur = (e)=>{
        let target = e.target as HTMLInputElement
        target.parentElement.style.borderBottom = "none"
    }
    return <div id="RecentJob">
        <div id="searchBox">
            <input type="text" onFocus={searchBoxFocus} onBlur={searchBoxBlur} />
            <div class="searchBtn"><i class="iconfont icon-sousuo"></i></div>
        </div>
        <div id="recentJobBox">
            <div>
                这是一个最近要发生的事件，这是一个最近要发生的事件，
            </div>
            <div>
                这是一个最近要发生的事件，这是一个最近要发生的事件，
            </div>
            <div>
                这是一个最近要发生的事件，这是一个最近要发生的事件，
            </div>
            <div>
                这是一个最近要发生的事件，这是一个最近要发生的事件，
            </div>
            <div>
                这是一个最近要发生的事件，这是一个最近要发生的事件，
            </div>
        </div>
    </div>
}