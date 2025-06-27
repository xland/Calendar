import { ModelSetting } from "./model/ModelSetting";

class DataSetting {
  setting: ModelSetting;
  getSkinName(index: number) {
    let arr = ["red", "green", "blue", "purple", "yellow"];
    return arr[this.setting.SkinDefault];
  }
  async init() {
    // let data = horse.db.sql(`SELECT * FROM Setting`, "db.db");
    // this.setting = data.data[0] as ModelSetting;
    // document.body.setAttribute("class", this.getSkinName(this.setting.SkinDefault));
  }
}
export let dataSetting = new DataSetting();
