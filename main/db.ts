import Database from 'better-sqlite3';
import { app } from 'electron';
import fsex from "fs-extra"
import path from "path"
import crypto from "crypto"
import { ModelJob } from '../model/ModelJob';

export class Db{
    db:Database.Database
    openDb(dbPath:string){
        try{
            this.db = new Database(dbPath,{ timeout:8000 })
            this.db.pragma('journal_mode = WAL');    
        }catch(ex){
            console.log(ex)
        }
    }
    createDb(dbPath:string){
        let sql = `CREATE TABLE Job(Id VARCHAR2(36) NOT NULL ON CONFLICT FAIL UNIQUE ON CONFLICT FAIL, 
CreateTime BIGINT,UpdateTime BIGINT,DeleteTime BIGINT,IsDelete BOOLEAN, 
JobInfo TEXT,RepeatType INT,RepeatTimes INT,RepeatEndDay INT,AlertBefore INT,StartTime BIGINT,EndTime BIGINT,ColorIndex INT);          
CREATE INDEX JobInfo_Index ON Job(JobInfo);`
        try{
            this.db = new Database(dbPath,{ timeout:8000 })
            this.db.pragma('journal_mode = WAL');
            this.db.exec(sql);
        }catch(ex){
            console.log(ex)
        }        
    }
    saveToDb(type:string,data:any){
        if(type === "Job"){
            data = data as ModelJob;
            data.Id = crypto.randomUUID()
            data.CreateTime = Date.now()
            data.UpdateTime = data.CreateTime
            data.IsDelete = 0
            let columnNames:string[] = []
            for(let key in data){
                columnNames.push(key);
            }
            let insertSql = `INSERT INTO Job (${columnNames.join(",")}) VALUES (@${columnNames.join(",@")})`            
            try{
                let insert = this.db.prepare(insertSql);
                insert.run(data)
            }catch(ex){
                console.log(ex)
            }
        }else if(type == ""){

        }
    }
    getData(sql:string,...params){
        let objs = this.db.prepare(sql).all(params);
        return objs;
    }
    updateData(sql:string,...params){
        try{
            this.db.prepare(sql).run(params)
        }catch(ex){
            console.log(ex)
        }        
    }
    init(){
        let dbPath = path.join(app.getPath("userData"),"db")         
        let exist = fsex.pathExistsSync(dbPath);
        if(exist){
            dbPath = path.join(dbPath,"db.db");
            exist = fsex.pathExistsSync(dbPath);
            if(exist){
                this.openDb(dbPath);
            }else{
                this.createDb(dbPath);
            } 
        }else{  
            fsex.mkdirSync(dbPath);
            dbPath = path.join(dbPath,"db.db");
            this.createDb(dbPath);             
        }
    }
}

