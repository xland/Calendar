import Database from 'better-sqlite3';
import { app } from 'electron';
import fsex from "fs-extra"
import path from "path"

export class Db{
    db:Database
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
            JobInfo TEXT,RepeatType INT,AlertBefore INT,StartTime BIGINT,EndTime BIGINT);          
          CREATE INDEX JobInfo_Index ON Job(JobInfo);
        `
        try{
            this.db = new Database(dbPath,{ timeout:8000 })
            this.db.pragma('journal_mode = WAL');
            this.db.exec(sql);
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

