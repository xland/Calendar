import React from "jsx-dom";
import "./Index.scss";
import LeftPanel from "./LeftPanel";
import MainPanel from "./MainPanel";
function App() {
  document.body.ondragstart = () => false;
  document.body.ondragend = () => false;
  document.body.ondrop = () => false;
  
  return (
    <>
      <LeftPanel></LeftPanel>
      <MainPanel></MainPanel>
    </>
  );
}
document.body.appendChild(<App />);
