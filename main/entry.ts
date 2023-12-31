import { protocol, app } from "electron";
import { main } from "./main";
import { db } from "./db";
import { schema } from "./schema";
import { tray } from "./tray";
process.env.ELECTRON_DISABLE_SECURITY_WARNINGS = "true";
protocol.registerSchemesAsPrivileged([{ scheme: "lun", privileges: { standard: true, supportFetchAPI: true, secure: true, corsEnabled: true } }]);

app.whenReady().then(() => {
  db.init();
  schema.init();
  main.init();
  tray.init();
});
