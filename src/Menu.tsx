import React from "./React";
import "./Menu.scss";
import { dataMonth } from "./DataMonth";
import { Helper } from "./common/Helper";
export default function (props) {
  let hideMenu = async (e) => {
    let target = e.target as HTMLElement;
    if (target.parentElement.getAttribute("id") === "Menu") {
      let id = target.parentElement.dataset.id;
      if (target.innerHTML === "增加") {
        let data = dataMonth.dateArr[dataMonth.getCurDateIndex()].jobs;
        let colorIndex = 0;
        if (data.length) {
          colorIndex = data[data.length - 1].ColorIndex + 1;
        }
        if (colorIndex > 5) colorIndex = 0;
        let startTime = new Date(data[0].StartTime);
        startTime.setHours(8, 0, 0, 0);
        window.open(`/IndexJob.html?colorIndex=${colorIndex}&startTime=${startTime.getTime()}`, "_blank", `{ "title": "增加日程" }`);
        Helper.$id("ModalMask").style.display = "block";
      } else if (target.innerHTML === "修改") {
        window.open(`/IndexJob.html?editId=${id}`, "_blank", `{ title: "修改日程" }`);
        Helper.$id("ModalMask").style.display = "block";
      } else {
        // let { ipcRenderer } = require("electron");
        // await ipcRenderer.invoke("excuteSQL", `delete from Job where id=?`, id);
        // dispatchEvent(new Event("refreshView"));
      }
    }
    Helper.$id("Menu").style.display = "none";
    document.removeEventListener("mousedown", hideMenu);
  };
  let show = (evt: CustomEvent) => {
    let menu = evt.target as HTMLElement;
    let e = evt.detail;
    let left = e.x + 8;
    let top = e.y + 3;
    if (window.innerWidth - left < 86) {
      left = e.x - 86;
    }
    if (window.innerHeight - top < 86) {
      top = top - 80;
    }
    menu.style.top = `${top}px`;
    menu.style.left = `${left}px`;
    menu.style.display = "block";
    menu.dataset.id = e.id;
    setTimeout(() => {
      document.addEventListener("mousedown", hideMenu);
    }, 10);
  };
  return (
    <div id="Menu" onShow={show}>
      <div>增加</div>
      <div>修改</div>
      <div>删除</div>
    </div>
  );
}
