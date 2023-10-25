import { ModelBase } from "./ModelBase";

export class ModelJob extends ModelBase{
    JobInfo:string
    RepeatType:number
    AlertBefore:number
    StartTime:number
    EndTime:number
}