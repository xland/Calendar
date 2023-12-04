import { ModelBase } from "./ModelBase";

export class ModelJob extends ModelBase{
    /**
     * 日程内容
     */
    JobInfo:string = ""
    /**
     * 0 不重复
     * 1 每天
     * 2 每个工作日
     * 3 每周几
     * 4 每月第几天
     * 5 每月倒数第几天
     * 6 每月第几个星期几
     * 7 每月倒数第几个星期几
     * 8 每年第几月第几日
     */
    RepeatType:number = 0
    /**
     * 任务开始时间
     */
    StartTime:number
    /**
     * 任务结束时间
     */
    EndTime:number
    /**
     * 任务颜色
     */
    ColorIndex:number
}