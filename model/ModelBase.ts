export class ModelBase{
    Id:string
    CreateTime:number
    UpdateTime:number
    DeleteTime:number
    IsDelete:boolean
    async initId(){
        let crypto = await import("crypto")
        this.Id = crypto.randomUUID()
    }
}