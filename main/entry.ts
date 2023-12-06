import { protocol,app } from "electron";
import { main } from "./main";
process.env.ELECTRON_DISABLE_SECURITY_WARNINGS = "true";
protocol.registerSchemesAsPrivileged([{ scheme:'liulun', privileges: { standard: true, supportFetchAPI: true, secure: true, corsEnabled: true } }])
app.whenReady().then(()=>{
    main.init();
})