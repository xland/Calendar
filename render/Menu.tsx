import React from "./React";
import "./Menu.scss";
export default function (props) {
  let hideMenu = (e) => {
    let target = e.target as HTMLElement;
    if (target.parentElement.getAttribute("id") === "Menu") {
      if (target.innerHTML === "增加") {
      } else if (target.innerHTML === "修改") {
      } else {
        alert(123);
      }
    }
    document.getElementById("Menu").style.display = "none";
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
    setTimeout(() => {
      document.addEventListener("mousedown", hideMenu);
    }, 10);
  };
  let addClick = (e: MouseEvent) => {};
  let editClick = (e: MouseEvent) => {};
  let delClick = (e: MouseEvent) => {
    alert(123);
    e.preventDefault();
    e.stopPropagation();
  };
  return (
    <div id="Menu" onShow={show}>
      <div>增加</div>
      <div>修改</div>
      <div>删除</div>
    </div>
  );
}
