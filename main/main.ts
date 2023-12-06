import path from 'path';
import url from "url"
import { app,BrowserWindow,ipcMain,protocol,net ,HandlerDetails} from "electron";
class Main {
    win:BrowserWindow;
    initProtocal(){
        protocol.handle('lun', (request) => {
            let filePath = request.url.slice('lun://'.length)
            console.log(filePath)
            let fetchPath = url.pathToFileURL(path.join(__dirname, filePath)).toString();
            fetchPath = decodeURIComponent(fetchPath)
            return net.fetch(fetchPath)
            // let url = request.url
            // let pathName = new URL(url).pathname
            // pathName = decodeURI(pathName)
            // let filePath = path.join(__dirname, pathName)
            // let fileStr = `file://${filePath}`
            // return net.fetch(fileStr)
            // let data = fs.readFileSync(filePath) //todo
            // return new Response(data)
        })
    }
    initHook(){ 
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
                if(item.id != this.win.id){
                    item.show();
                    break;
                }
            }
        })
    }
    listenWinEvent(win:BrowserWindow){
        win.addListener("maximize",()=>{
            win.webContents.send("windowStateChanged","maximize")
        })
        win.addListener("unmaximize",()=>{
            win.webContents.send("windowStateChanged","unmaximize")
        })
        if(this.win != win){
            win.once("close",()=>{
                this.win.webContents.send("modalWindowClosed")
            })
        }
    }
    winOpenHandler(e:HandlerDetails){
        let config = JSON.parse(e.features)
        let options = this.getWinOptions()
        Object.assign(options,config);
        if(this.win){        
            options.modal = true;
            options.parent = this.win
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
    handleWindowCreated(){
        app.addListener("browser-window-created",(e,target:BrowserWindow)=>{
            // @ts-ignore
            target.webContents.setWindowOpenHandler(this.winOpenHandler);
            target.webContents.openDevTools({mode:"undocked"});
            this.listenWinEvent(target)
        })
    }
    getWinOptions(){
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
        } as Electron.BrowserWindowConstructorOptions;
    }
    createMainWindow(){
        let options = this.getWinOptions();
        options.title = "日历";    
        options.minHeight = 800;
        options.minWidth = 1100;
        // fs.appendFileSync(path.join(app.getPath("userData"), "log.txt"),"start create window /n")
        this.win = new BrowserWindow(options);
        let serverUrl = process.argv[2]
        if(serverUrl){
            console.log(serverUrl)
            this.win.loadURL(serverUrl);
        }else{
            this.win.loadURL(`lun://./Index.html`)
        }
    }
    init(){
        this.initHook()
        this.initProtocal()
        this.handleWindowCreated()
        this.createMainWindow()
    }
}
export let main = new Main()