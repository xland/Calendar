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

class App extends React.Widget {
  static ready(){

  }
  render(){
    return (<span>{`测试测试不错不错`}</span>);
  }
}

document.addEventListener("DOMContentLoaded", async ()=>{
  document.body.ondragstart = () => false;
  document.body.ondragend = () => false;
  document.body.ondrop = () => false;
  await dataMonth.init();
  document.body.appendChild(<App />);
  App.ready()
})

