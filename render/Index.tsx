import React from "jsx-dom";
import "./Index.scss";
import TitleBar from "./TitleBar";
function App() {
  document.body.ondragstart = () => false;
  document.body.ondragend = () => false;
  document.body.ondrop = () => false;
  return (
    <>
      <TitleBar></TitleBar>
    </>
  );
}
document.body.appendChild(<App />);
