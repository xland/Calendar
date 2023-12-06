import { protocol,app } from "electron";
import { main } from "./main";
import { db } from "./db";
process.env.ELECTRON_DISABLE_SECURITY_WARNINGS = "true";
protocol.registerSchemesAsPrivileged([{ scheme:'lun', privileges: { standard: true, supportFetchAPI: true, secure: true, corsEnabled: true } }])
app.whenReady().then(()=>{
    db.init()
    main.init();
})