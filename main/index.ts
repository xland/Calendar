import { app,BrowserWindow,HandlerDetails,ipcMain,webContents } from "electron";
process.env.ELECTRON_DISABLE_SECURITY_WARNINGS = "true";
let win:BrowserWindow;
let initHook = ()=>{
    ipcMain.handle("changeWindowState",(e,state)=>{
        let win = BrowserWindow.fromWebContents(e.sender) as BrowserWindow;
        win[state]();
    })
    ipcMain.handle("getWindowState",(e)=>{
        let win = BrowserWindow.fromWebContents(e.sender) as BrowserWindow;
        return win.isMaximized();
    })
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

let winOpenHandler = (d:HandlerDetails)=>{
    let overrideBrowserWindowOptions = getWinOptions()
    overrideBrowserWindowOptions.title = "增加"
    return {
        action: 'allow', 
        outlivesOpener: true, 
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
    win.webContents.openDevTools({mode:"undocked"});
}
let winCreateHandler = (e,win:BrowserWindow)=>{
    // @ts-ignore
    win.webContents.setWindowOpenHandler(winOpenHandler);
    initListener(win)
}
let init = async ()=>{
    initHook();
    app.addListener("browser-window-created",winCreateHandler)
    await creatreWindow();
}
app.whenReady().then(init)