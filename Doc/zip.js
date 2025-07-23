
// "adm-zip": "^0.5.10",
// "fs-extra": "^11.2.0"

let start = async ()=>{
    let AdmZip = require("adm-zip");
    let fs = require("fs-extra")
    let path = require("path")
    console.log("start1",Date.now())
    let zip = new AdmZip("./test/1.zip");
    let zipEntries = zip.getEntries(); 
    console.log("start2",Date.now())
    let destPath = "./test/out"
    let fileSize = 0;
    let offset = 0;
    for(let entry of zipEntries){
        fileSize += entry.header.size
    }
    console.log(fileSize,"percent:","0%") 
    for(let entry of zipEntries){
        let filePath = path.join(destPath,entry.entryName);
        if(!entry.isDirectory){
            await fs.ensureDir(path.dirname(filePath))
            entry.getDataAsync(async (data,err)=>{
                fs.appendFile(filePath,data)
                offset+=data.length;
                console.log(fileSize,"percent:",`${offset/fileSize*100}%`) 
            })
        }
    }
}
start()