import "./Index.scss";
import LeftPanel from "./LeftPanel";
import MainPanel from "./MainPanel";
import { dataMonth } from "./DataMonth";
import React from "./React";
import ModalMask from "./ModalMask";
import { eventer } from "../common/eventer";
import { dataSetting } from "./DataSetting";
import Menu from "./Menu";
import { dataMonthSmall } from "./DataMonthSmall";
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

let connDb = async () => {
  let data = await horse.db.open("db.db");
  console.log(data);
  if (data.ok && data.isDbFirstCreated) {
    let sqlData = await horse.db.sql(`CREATE TABLE Job(Id VARCHAR2(36) NOT NULL ON CONFLICT FAIL UNIQUE ON CONFLICT FAIL,JobInfo TEXT,RepeatType INT,StartTime BIGINT,EndTime BIGINT,ColorIndex INT);
CREATE INDEX JobInfo_Index ON Job(JobInfo);
CREATE TABLE Setting(ViewDefault INT DEFAULT 0,ViewVal Int,LangDefault INT DEFAULT 0,SkinDefault INT DEFAULT 0,AlertBefore INT);
INSERT INTO Setting (ViewDefault,ViewVal,LangDefault,SkinDefault,AlertBefore) VALUES (0,0,0,0,5);`, "db.db");
    console.log(sqlData);
  }
}

document.addEventListener("DOMContentLoaded", async () => {
  document.body.ondragstart = () => false;
  document.body.ondragend = () => false;
  document.body.ondrop = () => false;
  document.body.appendChild(<App />);
  await connDb();
  await dataMonth.init();
  dataMonthSmall.initFirst();
  await dataSetting.init();
  eventer.emit("dataReady");
  // let { ipcRenderer } = require("electron");
  // ipcRenderer.invoke("changeWindowState", "show");
  window.addEventListener("refreshView", async (e) => {
    await dataMonth.initJobArr();
    await dataMonthSmall.init();
    eventer.emit("dataReady");
  });
});
