import path from "path";
import { Tray as TrayObj, Menu, app } from "electron";
import { main } from "./main";
class Tray {
  tray: TrayObj;
  trayClick() {
    main.win.show();
  }
  exit() {
    app.exit();
  }
  async init() {
    this.tray = new TrayObj(path.join(__dirname, "res/icon.png"));
    let contextMenu = Menu.buildFromTemplate([
      {
        label: "退出",
        click: () => {
          this.exit();
        },
      },
    ]);
    this.tray.setContextMenu(contextMenu);
    this.tray.addListener("click", () => this.trayClick());
  }
}
export let tray = new Tray();
