export class Helper{
    static $id(id:string){
        return document.getElementById(id)
    }
    static $select(name:string){
        return document.querySelector(name)
    }
}