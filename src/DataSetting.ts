import { ModelSetting } from "./model/ModelSetting";
import { db } from "./common/db";
class DataSetting {
  setting: ModelSetting;
  getSkinName(index: number) {
    let arr = ["red", "green", "blue", "purple", "yellow"];
    return arr[this.setting.SkinDefault];
  }
  async init() {
    let sql = `SELECT * FROM Setting`;
    let data = await db.exec(sql);
    this.setting = data[0] as ModelSetting;
    document.body.setAttribute("class", this.getSkinName(this.setting.SkinDefault));
  }
}
export let dataSetting = new DataSetting();
