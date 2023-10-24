import { app,BrowserWindow,HandlerDetails,ipcMain,webContents } from "electron";
import { spawn } from "child_process";
import path from "path";
process.env.ELECTRON_DISABLE_SECURITY_WARNINGS = "true";
let win:BrowserWindow;
let server;
let initHook = ()=>{
    ipcMain.handle("changeWindowState",(e,state)=>{
        let win = BrowserWindow.fromWebContents(e.sender) as BrowserWindow;
        win[state]();
    })
    ipcMain.handle("getWindowState",(e)=>{
        let win = BrowserWindow.fromWebContents(e.sender) as BrowserWindow;
        return win.isMaximized();
    })
    ipcMain.handle("callServer",(e,cmd)=>{
        if(cmd === "startServer"){
            let serverPath = path.join(process.cwd(),"server/Windows") ;
            server = spawn(path.join(serverPath,"pikafish.exe"),{cwd:serverPath})
            server.stdin.setEncoding('utf-8');            
            server.stdout.on('data', (data) => {
                console.log(data.toString("utf8"));
            });
        }else{
            server.stdin.cork();
            server.stdin.write(`${cmd}\n`);
            server.stdin.uncork();
        }
    })
}
let initListener = ()=>{
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
    // @ts-ignore
    win.webContents.setWindowOpenHandler(winOpenHandler);
    initListener();
    console.log(process.argv[2]);
    await win.loadURL(process.argv[2]);
    win.show();
    win.webContents.openDevTools({mode:"undocked"});
}
let init = async ()=>{
    initHook();
    await creatreWindow();
}
app.whenReady().then(init)