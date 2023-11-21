import { ModelSetting } from "../model/ModelSetting";

class DataSetting{
    setting:ModelSetting
    async init(){
        let {ipcRenderer} = require("electron")
        this.setting = await ipcRenderer.invoke("getSetting")
    }
}
export let dataSetting = new DataSetting();
