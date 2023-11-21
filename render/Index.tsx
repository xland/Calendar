import "./Index.scss";
import LeftPanel from "./LeftPanel";
import MainPanel from "./MainPanel";
import { dataMonth } from "./DataMonth";
import React from "./React";
import ModalMask from "./ModalMask";
import { eventer } from "../common/eventer";
import { dataSetting } from "./DataSetting";
let App = () => {
  return (
    <>
      <LeftPanel />
      <MainPanel />
      <ModalMask />
    </>
  );
};
document.addEventListener("DOMContentLoaded", async () => {
  document.body.ondragstart = () => false;
  document.body.ondragend = () => false;
  document.body.ondrop = () => false;
  document.body.appendChild(<App />);
  await dataMonth.init();
  await dataSetting.init();
  eventer.emit("dataReady");
  window.addEventListener("saveJobOk", async (e) => {
    await dataMonth.initJobArr();
    eventer.emit("dataReady");
  });
});
