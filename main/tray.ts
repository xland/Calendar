import path from "path";
import { Tray as TrayObj, Menu, app, shell } from "electron";
import { main } from "./main";
class Tray {
  tray: TrayObj;
  trayClick() {
    main.win.show();
  }
  exit() {
    app.exit();
  }
  goToIssuePage() {
    shell.openExternal("https://github.com/xland/Calendar/issues");
  }
  showMenu() {
    let contextMenu = Menu.buildFromTemplate([
      {
        label: "反馈问题",
        click: () => {
          this.goToIssuePage();
        },
      },
      {
        label: "显示窗口",
        click: () => {
          this.trayClick();
        },
      },
      {
        label: "退出应用",
        click: () => {
          this.exit();
        },
      },
    ]);
    this.tray.popUpContextMenu(contextMenu);
  }
  async init() {
    this.tray = new TrayObj(path.join(__dirname, "res/icon.png"));
    this.tray.addListener("click", () => this.trayClick());
    this.tray.on("right-click", () => this.showMenu());
  }
}
export let tray = new Tray();
