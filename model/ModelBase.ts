import crypto from "crypto"
export class ModelBase{
    Id:string
    CreateTime:number
    UpdateTime:number
    DeleteTime:number
    IsDelete:boolean
    initId(){
        this.Id = crypto.randomUUID()
    }
}