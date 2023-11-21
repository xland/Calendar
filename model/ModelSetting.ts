import { ModelBase } from "./ModelBase";

export class ModelSetting extends ModelBase{
    ViewDefault:number
    OpenAtLogin:boolean    
    /**
    * 提前几分钟提醒
    */
   AlertBefore:number
}