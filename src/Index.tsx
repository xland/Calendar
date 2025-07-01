import "./Index.scss";
import LeftPanel from "./LeftPanel";
import MainPanel from "./MainPanel";
import { dataMonth } from "./DataMonth";
import React from "./React";
import ModalMask from "./ModalMask";
import { eventer } from "./common/eventer";
import { dataSetting } from "./DataSetting";
import Menu from "./Menu";
import { dataMonthSmall } from "./DataMonthSmall";
import { db } from "./common/db";

let App = () => {
  return (
    <>
      <LeftPanel />
      <MainPanel />
      <ModalMask />
      <Menu />
    </>
  );
};

document.addEventListener("DOMContentLoaded", async () => {
  document.body.ondragstart = () => false;
  document.body.ondragend = () => false;
  document.body.ondrop = () => false;
  document.body.appendChild(<App />);
  await db.open();
  await dataMonth.init();
  dataMonthSmall.initFirst();
  await dataSetting.init();
  eventer.emit("dataReady");
  const channel = new BroadcastChannel('winChannel');
  channel.onmessage = async (e) => {
    if (e.data === "refreshView") {
      await dataMonth.initJobArr();
      await dataMonthSmall.init();
      eventer.emit("dataReady");
    }
  };
});
