import { ModelSetting } from "../model/ModelSetting";

class DataSetting{
    setting:ModelSetting
    async init(){
        let {ipcRenderer} = require("electron")
        let objs = await ipcRenderer.invoke("getData","SELECT * FROM Setting")
        this.setting = objs[0]
    }
}
export let dataSetting = new DataSetting();
