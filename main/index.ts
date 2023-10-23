import { app,BrowserWindow,ipcMain,webContents } from "electron";
import { spawn } from "child_process";
import path from "path";
process.env.ELECTRON_DISABLE_SECURITY_WARNINGS = "true";
let win;
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
let creatreWindow = async ()=>{
    win = new BrowserWindow(
        {
            frame:false,
            minHeight:800,
            minWidth:1100,
            title:"日历",
            webPreferences:{
                allowRunningInsecureContent: true,
                contextIsolation: false,
                nodeIntegration:true,
                sandbox:false,
                webSecurity:false,
            }
        }
    );
    initListener();
    await win.loadURL(process.argv[2]);
    win.show();
    win.webContents.openDevTools({mode:"undocked"});
}
let init = async ()=>{
    initHook();
    await creatreWindow();
}
app.whenReady().then(init)