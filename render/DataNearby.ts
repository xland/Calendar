import { ModelJob } from './../model/ModelJob';
class DataNearby{
    jobs:ModelJob[]
    async init(){
        let {ipcRenderer} = require("electron")
        this.setting = await ipcRenderer.invoke("getSetting")
    }
}