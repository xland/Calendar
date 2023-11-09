// import React from "jsx-dom";
import "./Index.scss";
import LeftPanel from "./LeftPanel";
import MainPanel from "./MainPanel";
import { dataMonth } from "./DataMonth";
import React from "./React";
// class App extends React.Component {
//   static ready(){

//   }
//   render(){
//     return (
//       <>
//         <LeftPanel></LeftPanel>
//         <MainPanel></MainPanel>
//       </>
//     );
//   }
// }

// class App extends React.Widget {
//   static ready(){

//   }
//   render(){
//     return (<span>{`测试测试不错不错`}</span>);
//   }
//   constructor(){
//     super()
    
//     document.addEventListener("DOMContentLoaded", async ()=>{
//       console.log("aaa")
//     })
//   }
// }

let App = ()=>{
  let click = ()=>{
    alert(1);
  }
  return <div style="background:#ddd" onClick={click}>
    <p>测试测试</p>
    </div>
}

document.body.appendChild(<App style="font-size:18px" />);

document.addEventListener("DOMContentLoaded", async ()=>{
  document.body.ondragstart = () => false;
  document.body.ondragend = () => false;
  document.body.ondrop = () => false;
  await dataMonth.init();
  
  // App.ready()
})

