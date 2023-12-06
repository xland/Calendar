import path  from 'path';
import fs from  "fs"
import { app,BrowserWindow,HandlerDetails,ipcMain,protocol,dialog } from "electron";
import { Db } from "./db";

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
    let options = getWinOptions()
    Object.assign(options,config);
    if(win){        
        options.modal = true;
        options.parent = win
        options.width = 480
        options.height = 380        
        options.minHeight = 380
        options.minWidth = 480
    }
    return {
        action: 'allow', 
        outlivesOpener: false, 
        overrideBrowserWindowOptions:options
    };
}

let createMainWindow = ()=>{
    let options = getWinOptions();
    options.title = "日历";    
    options.minHeight = 800;
    options.minWidth = 1100;
    // fs.appendFileSync(path.join(app.getPath("userData"), "log.txt"),"start create window /n")
    win = new BrowserWindow(options);
    let serverUrl = process.argv[2]
    if(serverUrl){
        console.log(serverUrl)
        win.loadURL(serverUrl);
    }else{
        // fs.appendFileSync(path.join(app.getPath("userData"), "log.txt"),"load url /n")
        win.loadURL(`liulun://./Index.html`)
    }
    // fs.appendFileSync(path.join(app.getPath("userData"), "log.txt"),"created window /n")
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
        fs.appendFileSync(path.join(app.getPath("userData"), "log.txt"),"url to path:"+filePath)
        let data = fs.readFileSync(filePath) //todo
        fs.appendFileSync(path.join(app.getPath("userData"), "log.txt"),"data:"+data)
        return new Response(data)
    })
    initDb();
    initHook();
    app.addListener("browser-window-created",winCreatedHandler)
    await createMainWindow();
}
app.whenReady().then(init)