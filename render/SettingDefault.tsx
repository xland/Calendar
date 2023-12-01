import { dataSetting } from "./DataSetting";
import React from "./React";
import "./SettingDefault.scss";
import { Helper } from "../common/Helper";
export default function (props) {
  let setCheckBox = (icon: HTMLElement, flag: boolean) => {
    if (flag) {
      icon.classList.remove("icon-uncheck");
      icon.classList.add("icon-check");
    } else {
      icon.classList.remove("icon-check");
      icon.classList.add("icon-uncheck");
    }
  };
  let setDefaultView = (target: HTMLElement) => {
    let icon = target.parentElement.querySelector(".icon-woderilixuanzhong") as HTMLElement;
    icon.classList.remove("icon-woderilixuanzhong");
    icon.classList.add("icon-jietutubiao_yuan");
    target.firstElementChild.firstElementChild.classList.add("icon-woderilixuanzhong");
  };
  let checkOneItem = (e: MouseEvent) => {
    let target = e.target as HTMLElement;
    if (target.tagName === "I") {
      target = target.parentElement.parentElement;
    } else if (target.tagName === "DIV") {
      target = target.parentElement;
    }
    if (!target.classList.contains("radioItem")) {
      return;
    }
    if (target.firstElementChild.firstElementChild.classList.contains("icon-woderilixuanzhong")) {
      return;
    }
    setDefaultView(target);
    return target;
  };
  let openAtLoginClick = async (e: MouseEvent) => {
    let icon = Helper.$id("openAtLoginIcon");
    let flag = !icon.classList.contains("icon-check");
    let { ipcRenderer } = require("electron");
    await ipcRenderer.invoke("setOpenAtLogin", flag);
    dataSetting.setting.OpenAtLogin = flag;
    setCheckBox(icon, flag);
    return false;
  };
  let defaultViewClick = async (e: MouseEvent) => {
    let target = checkOneItem(e);
    let val = Number(target.dataset.index);
    let { ipcRenderer } = require("electron");
    let sql = `Update Setting set ViewDefault = ?`;
    await ipcRenderer.invoke("excuteSQL", sql, val);
    dataSetting.setting.ViewDefault = val;
  };
  let defaultLangClick = async (e: MouseEvent) => {
    let target = checkOneItem(e);
    let val = Number(target.dataset.index);
    let { ipcRenderer } = require("electron");
    let sql = `Update Setting set LangDefault = ?`;
    await ipcRenderer.invoke("excuteSQL", sql, val);
    dataSetting.setting.LangDefault = val;
  };
  let alertBeforeClick = async (e: MouseEvent) => {
    let target = checkOneItem(e);
    let val = Number(target.dataset.index);
    let { ipcRenderer } = require("electron");
    let sql = `Update Setting set AlertBefore = ?`;
    await ipcRenderer.invoke("excuteSQL", sql, val);
    dataSetting.setting.AlertBefore = val;
  };
  let defaultSkinClick = async (e: MouseEvent) => {
    let target = checkOneItem(e);
    let val = Number(target.dataset.index);
    let { ipcRenderer } = require("electron");
    let sql = `Update Setting set SkinDefault = ?`;
    await ipcRenderer.invoke("excuteSQL", sql, val);
    dataSetting.setting.SkinDefault = val;
  };
  let loaded = async () => {
    let icon = Helper.$id("openAtLoginIcon");
    setCheckBox(icon, dataSetting.setting.OpenAtLogin);
    let row = Helper.$id("defaultViewRow");
    let dom = row.children[dataSetting.setting.ViewDefault + 1] as HTMLElement;
    setDefaultView(dom);

    row = row.nextElementSibling as HTMLElement;
    dom = row.children[dataSetting.setting.LangDefault + 1] as HTMLElement;
    setDefaultView(dom);

    row = row.nextElementSibling as HTMLElement;
    dom = row.children[dataSetting.setting.AlertBefore + 1] as HTMLElement;
    setDefaultView(dom);

    row = row.nextElementSibling as HTMLElement;
    dom = row.children[dataSetting.setting.SkinDefault + 1] as HTMLElement;
    setDefaultView(dom);
  };
  return (
    <div class="settingBox" id="settingDefault" onLoaded={loaded}>
      <div id="defaultViewRow" class="settingRow" onClick={defaultViewClick}>
        <div>默认视图：</div>
        <div class="radioItem" data-index="0">
          <div>
            <i class="iconfont icon-woderilixuanzhong"></i>
          </div>
          <div>日</div>
        </div>
        <div class="radioItem" data-index="1">
          <div>
            <i class="iconfont icon-jietutubiao_yuan"></i>
          </div>
          <div>周</div>
        </div>
        <div class="radioItem" data-index="2">
          <div>
            <i class="iconfont icon-jietutubiao_yuan"></i>
          </div>
          <div>月</div>
        </div>
        <div class="radioItem" data-index="3">
          <div>
            <i class="iconfont icon-jietutubiao_yuan"></i>
          </div>
          <div>记住上次视图</div>
        </div>
      </div>
      <div id="langRow" class="settingRow" onClick={defaultLangClick}>
        <div>默认语言：</div>
        <div class="radioItem" data-index="0">
          <div>
            <i class="iconfont icon-woderilixuanzhong"></i>
          </div>
          <div>简体中文</div>
        </div>
        <div class="radioItem" data-index="1">
          <div>
            <i class="iconfont icon-jietutubiao_yuan"></i>
          </div>
          <div>繁体中文</div>
        </div>
        <div class="radioItem" data-index="2">
          <div>
            <i class="iconfont icon-jietutubiao_yuan"></i>
          </div>
          <div>英文</div>
        </div>
      </div>
      <div id="langRow" class="settingRow" onClick={alertBeforeClick}>
        <div>提前提醒：</div>
        <div class="radioItem" data-index="0">
          <div>
            <i class="iconfont icon-jietutubiao_yuan"></i>
          </div>
          <div>5分钟</div>
        </div>
        <div class="radioItem" data-index="1">
          <div>
            <i class="iconfont icon-woderilixuanzhong"></i>
          </div>
          <div>15分钟</div>
        </div>
        <div class="radioItem" data-index="2">
          <div>
            <i class="iconfont icon-jietutubiao_yuan"></i>
          </div>
          <div>30分钟</div>
        </div>
      </div>
      <div id="langRow" class="settingRow" onClick={defaultSkinClick}>
        <div>系统皮肤：</div>
        <div class="radioItem" data-index="0">
          <div>
            <i class="iconfont icon-jietutubiao_yuan"></i>
          </div>
          <div>红</div>
        </div>
        <div class="radioItem" data-index="1">
          <div>
            <i class="iconfont icon-woderilixuanzhong"></i>
          </div>
          <div>绿</div>
        </div>
        <div class="radioItem" data-index="2">
          <div>
            <i class="iconfont icon-jietutubiao_yuan"></i>
          </div>
          <div>蓝</div>
        </div>
      </div>
      <div class="settingRow" onClick={openAtLoginClick}>
        <div>
          <i id="openAtLoginIcon" class="iconfont icon-uncheck"></i>
        </div>
        <div>开机自启动</div>
      </div>
      <div class="settingRow">
        <div>
          <i class="iconfont icon-uncheck"></i>
        </div>
        <div>显示农历</div>
      </div>
    </div>
  );
}
