import { ModelSetting } from "../model/ModelSetting";

class DataSetting {
  setting: ModelSetting;
  getSkinName(index: number) {
    let arr = ["red", "green", "blue", "purple", "yellow"];
    return arr[this.setting.SkinDefault];
  }
  async init() {
    // let { ipcRenderer } = require("electron");
    // this.setting = await ipcRenderer.invoke("getSetting");
    // let arr = ["red", "green", "blue", "purple"];
    // document.body.setAttribute("class", this.getSkinName(this.setting.SkinDefault));
  }
}
export let dataSetting = new DataSetting();
