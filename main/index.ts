import path  from 'path';
import fs from  "fs"
import { app,BrowserWindow,HandlerDetails,ipcMain,protocol } from "electron";
import { Db } from "./db";
import { ModelSetting } from "../model/ModelSetting";

process.env.ELECTRON_DISABLE_SECURITY_WARNINGS = "true";
protocol.registerSchemesAsPrivileged([{ scheme:'liulun', privileges: { standard: true, supportFetchAPI: true, secure: true, corsEnabled: true } }])
let win:BrowserWindow;
let db:Db


let initHook = ()=>{ 
    ipcMain.handle("changeWindowState",(e,state)=>{
        let win = BrowserWindow.fromWebContents(e.sender) as BrowserWindow;
        win[state]();
    })
    ipcMain.handle("getWindowState",(e)=>{
        let win = BrowserWindow.fromWebContents(e.sender) as BrowserWindow;
        return win.isMaximized();
    })
    ipcMain.handle("getData",(e,sql:string,...params)=>{
        return db.getData(sql,...params);
    })
    ipcMain.handle("excuteSQL",(e,sql:string,...params)=>{
        db.excuteSQL(sql,...params);
        win.show();
    })
    ipcMain.handle("getSetting",()=>{
        let setting:ModelSetting = db.getData(`SELECT * FROM Setting`)[0] as ModelSetting
        setting.OpenAtLogin = app.getLoginItemSettings().openAtLogin
        return setting;
    })
    ipcMain.handle("getDataRecent",(e)=>{
        return db.getDataRecent()
    })
    ipcMain.handle("getDataOneMonth",(e,startTime:number,endTime:number)=>{
        return db.getDataOneMonth(startTime,endTime)
    })
    ipcMain.handle("hasDataOneMonth",(e,startTime:number,endTime:number)=>{
        return db.hasDataOneMonth(startTime,endTime)
    })
    ipcMain.handle("setOpenAtLogin",(e,flag:boolean)=>{
        app.setLoginItemSettings({openAtLogin:flag});
    })
    ipcMain.handle("activeSubWindow",(e)=>{
        let wins = BrowserWindow.getAllWindows();
        for(let item of wins){
            if(item.id != win.id){
                item.show();
                break;
            }
        }
    })
}
let initDb = ()=>{
    db = new Db();
    db.init();
}
let initListener = (win:BrowserWindow)=>{
    win.addListener("maximize",()=>{
        win.webContents.send("windowStateChanged","maximize")
    })
    win.addListener("unmaximize",()=>{
        win.webContents.send("windowStateChanged","unmaximize")
    })
}

let getWinOptions:()=>Electron.BrowserWindowConstructorOptions = ()=>{
    return {
        frame:false,
        show:false,
        webPreferences:{
            allowRunningInsecureContent: true,
            contextIsolation: false,
            nodeIntegration:true,
            sandbox:false,
            webSecurity:false,
        }
    };
}

let winOpenHandler = (e:HandlerDetails)=>{
    let config = JSON.parse(e.features)
    let overrideBrowserWindowOptions = getWinOptions()
    Object.assign(overrideBrowserWindowOptions,config.winConfig);
    if(win){        
        config.winConfig.modal = true;
        config.winConfig.parent = win
    }
    return {
        action: 'allow', 
        outlivesOpener: false, 
        overrideBrowserWindowOptions
    };
}

let createMainWindow = ()=>{
    let options = getWinOptions();
    options.title = "日历";    
    options.minHeight = 800;
    options.minWidth = 1100;
    win = new BrowserWindow(options);
    let serverUrl = process.argv[2]
    if(serverUrl){
        console.log(serverUrl)
        win.loadURL(serverUrl);
    }else{
        win.loadURL(`liulun://./index.html`)
    }
}
let winCreatedHandler = (e,target:BrowserWindow)=>{
    // @ts-ignore
    target.webContents.setWindowOpenHandler(winOpenHandler);
    target.webContents.openDevTools({mode:"undocked"});
    initListener(target)
    if(target != win){
        target.once("close",()=>{
            win.webContents.send("modalWindowClosed")
        })
    }
}
let init = async ()=>{
    protocol.handle('liulun', (request) => {
        let url = request.url
        let pathName = new URL(url).pathname
        pathName = decodeURI(pathName)
        let filePath = path.join(__dirname, pathName)
        let data = fs.readFileSync(filePath)
        return new Response(data)
    })
    initDb();
    initHook();
    app.addListener("browser-window-created",winCreatedHandler)
    await createMainWindow();
}
app.whenReady().then(init)