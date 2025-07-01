import React from "./React";
import TitleBarBtns from "./TitleBarBtns";
import ColorGet from "./ColorGet";
import { ModelJob } from "./model/ModelJob";
import { db } from "./common/db";
import "./IndexAlert.scss";
function App(props) {
  let job = props.job as ModelJob;
  let save = () => {
    horse.win.close()
  };
  return (
    <>
      <div class="titleBar">
        <div class="title">事务提醒</div>
        <TitleBarBtns></TitleBarBtns>
      </div>
      <div class="content">{job.JobInfo}</div>
      <div class="btnBox">
        <div class="btnSave" onClick={save}>
          知道了
        </div>
      </div>
    </>
  );
}
document.addEventListener("DOMContentLoaded", async () => {
  let url = new URL(window.location.href);
  let id = url.searchParams.get("id");
  let [job]: ModelJob[] = await db.exec(`SELECT * FROM Job WHERE Id = '${id}'`);
  document.body.style.setProperty("--color", ColorGet(job.ColorIndex));
  document.body.appendChild(<App job={job} />);
});
