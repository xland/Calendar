import { ModelBase } from "./ModelBase";

export class ModelSetting extends ModelBase{
    ViewDefault:number
    ViewVal:number
    LangDefault:number
    OpenAtLogin:boolean
    SkinDefault:number
    /**
    * 提前几分钟提醒
    */
   AlertBefore:number
}