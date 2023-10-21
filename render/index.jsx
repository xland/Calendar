import React from "jsx-dom";
import "./index.css";
import TitleBar from "./TitleBar";
import CenterBox from "./CenterBox";
import StatusBar from "./StatusBar";
function App() {
  document.body.ondragstart = () => false;
  document.body.ondragend = () => false;
  document.body.ondrop = () => false;
  return (
    <>
      <TitleBar></TitleBar>
      <CenterBox></CenterBox>
      <StatusBar></StatusBar>
    </>
  );
}
document.body.appendChild(<App />);
