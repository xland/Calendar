import React from "./React";
import "./IndexJob.scss";
import TitleBarBtns from "./TitleBarBtns";
import IndexJobBox from "./IndexJobBox";
import ColorGet from "./ColorGet";
import { ModelJob } from "./model/ModelJob";
import { Helper } from "./common/Helper";
import { db } from "./common/db";
function App(props) {
  let getJob = () => {
    let timeBox = Helper.$id("IndexJobBox").firstElementChild;
    let year = parseInt(timeBox.children[0].innerHTML);
    let month = parseInt(timeBox.children[1].innerHTML);
    let date = parseInt(timeBox.children[2].innerHTML);
    let hour0 = parseInt(timeBox.children[3].innerHTML);
    let minute0 = parseInt(timeBox.children[4].innerHTML);
    let hour1 = parseInt(timeBox.children[6].innerHTML);
    let minute1 = parseInt(timeBox.children[7].innerHTML);
    let job = new ModelJob();
    job.StartTime = new Date(year, month - 1, date, hour0, minute0, 0, 0).getTime();
    job.EndTime = new Date(year, month - 1, date, hour1, minute1, 0, 0).getTime();
    let repeatDom = timeBox.nextElementSibling;
    let repeatOption = repeatDom.nextElementSibling;
    for (let i = 0; i < 5; i++) {
      if (repeatOption.children[i].innerHTML === repeatDom.innerHTML) {
        job.RepeatType = i;
        break;
      }
    }
    let taEle = Helper.$id("jobInfo") as HTMLTextAreaElement;
    let inputId = taEle.nextElementSibling as HTMLInputElement;
    job.JobInfo = taEle.value;
    job.Id = inputId.value;
    job.ColorIndex = props.colorIndex;
    return job;
  };

  let save = async () => {
    let job = getJob();
    if (job.Id) {
      let sql = `Update Job set JobInfo = "${job.JobInfo}",StartTime = ${job.StartTime} ,EndTime = ${job.EndTime} where Id = '${job.Id}'`;
      await db.exec(sql);
    } else {
      job.Id = Helper.getGUID();
      let sql = `INSERT INTO Job (Id,JobInfo,StartTime,EndTime,RepeatType,ColorIndex) VALUES ('${job.Id}', '${job.JobInfo}', ${job.StartTime}, ${job.EndTime}, ${job.RepeatType}, ${job.ColorIndex})`;
      await db.exec(sql);
    }
    const channel = new BroadcastChannel('winChannel');
    channel.postMessage('refreshView');
    horse.win.close();
  };
  return (
    <>
      <div class="titleBar">
        <div class="title">增加日程</div>
        <TitleBarBtns></TitleBarBtns>
      </div>
      <IndexJobBox></IndexJobBox>
      <div class="btnBox">
        <div class="btnSave" onClick={save}>
          保存
        </div>
      </div>
    </>
  );
}

document.addEventListener("DOMContentLoaded", async () => {
  await db.open();
  let url = new URL(window.location.href);
  let editId = url.searchParams.get("editId");
  let job: ModelJob;
  if (editId) {
    let jobArr: ModelJob[] = await db.exec(`SELECT * FROM Job WHERE Id = '${editId}'`);
    if (jobArr.length) {
      job = jobArr[0];
    }
  } else {
    job = new ModelJob();
    job.StartTime = Number(url.searchParams.get("startTime"));
    let endTime = new Date(job.StartTime);
    endTime.setHours(endTime.getHours() + 1);
    job.EndTime = endTime.getTime();
    job.ColorIndex = Number(url.searchParams.get("colorIndex"));
    job.JobInfo = "";
    job.Id = "";
  }
  document.body.style.setProperty("--color", ColorGet(job.ColorIndex));
  document.body.appendChild(<App colorIndex={job.ColorIndex} />);
  if (job.Id) {
    let title = document.querySelector(".title") as HTMLElement;
    title.innerHTML = "修改日程";
  }
  Helper.$select(".titleBar > .title").addEventListener("mousedown", () => {
    horse.win.startDrag();
  });
  let event = new CustomEvent("loaded", { detail: job });
  Helper.$id("IndexJobBox").dispatchEvent(event);
});
