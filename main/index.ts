import { app,BrowserWindow,HandlerDetails,ipcMain } from "electron";
import { Db } from "./db";
process.env.ELECTRON_DISABLE_SECURITY_WARNINGS = "true";
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
    ipcMain.handle("saveToDb",(e,type,data)=>{
        db.saveToDb(type,data);
        win.webContents.send("saveToDbOk")
        let subWin = BrowserWindow.fromWebContents(e.sender) as BrowserWindow;
        subWin.close();
    })
    ipcMain.handle("getData",(e,sql:string,...params)=>{
        return db.getData(sql,...params);
    })
    ipcMain.handle("updateData",(e,sql:string,...params)=>{
        return db.updateData(sql,...params);
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
        config.winConfig.modal = true
        config.winConfig.parent = win
    }
    console.log(config.winConfig)
    return {
        action: 'allow', 
        outlivesOpener: false, 
        overrideBrowserWindowOptions
    };
}

let creatreWindow = async ()=>{
    let options = getWinOptions();
    options.title = "日历";    
    options.minHeight = 800;
    options.minWidth = 1100;
    win = new BrowserWindow(options);
    console.log(process.argv[2]);
    await win.loadURL(process.argv[2]);
    win.show();
}
let winCreatedHandler = (e,target:BrowserWindow)=>{
    // @ts-ignore
    target.webContents.setWindowOpenHandler(winOpenHandler);
    target.webContents.openDevTools({mode:"undocked"});
    initListener(target)
    if(target != win){
        target.setParentWindow(win);
    }
}
let init = async ()=>{
    initDb();
    initHook();
    app.addListener("browser-window-created",winCreatedHandler)
    await creatreWindow();
}
app.whenReady().then(init)