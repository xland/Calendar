import { protocol,net} from "electron";
import url from "url"
import path from 'path';
class Schema{
    init(){
        protocol.handle('lun', (request) => {
            let filePath = request.url.slice('lun://'.length)
            let fetchPath = url.pathToFileURL(path.join(__dirname, filePath)).toString();
            fetchPath = decodeURIComponent(fetchPath)
            return net.fetch(fetchPath)
        })
    }
}
export let schema = new Schema();