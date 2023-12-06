import path from 'path';
import fs  from 'fs';
import { app,BrowserWindow,HandlerDetails,ipcMain,protocol,dialog } from "electron";
class Main {
    initProtocal(){
        protocol.handle('liulun', (request) => {
            let url = request.url
            let pathName = new URL(url).pathname
            pathName = decodeURI(pathName)
            let filePath = path.join(__dirname, pathName)
            let data = fs.readFileSync(filePath) //todo
            return new Response(data)
        })
    }
    init(){
        this.initProtocal()
    }
}
export let main = new Main()