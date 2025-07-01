export class Helper {
  static $id(id: string): HTMLElement {
    return document.getElementById(id);
  }
  static $select(name: string): HTMLElement {
    return document.querySelector(name);
  }
  static isCurrentDate(date: Date) {
    let now = new Date();
    return now.getFullYear() === date.getFullYear() && now.getMonth() === date.getMonth() && now.getDate() === date.getDate();
  }
  static showJobMenu(e: MouseEvent) {
    if (e.button != 2) return;
    let target = e.currentTarget as HTMLElement;
    let evt = new CustomEvent("show", { detail: { x: e.x, y: e.y, id: target.dataset.id } });
    let menu = Helper.$id("Menu");
    menu.dispatchEvent(evt);
    return false;
  }
  /**
   * 得到一个月的日期
   * @param tarDate 当前日期
   * @returns 返回一个数组
   */
  static getOneMonthDate(tarDate: Date) {
    let result = [];
    let year = tarDate.getFullYear();
    let month = tarDate.getMonth();
    let preMonthLastDay = new Date(year, month, 0);
    let weekIndex = preMonthLastDay.getDay();
    weekIndex = weekIndex === 0 ? 7 : weekIndex;
    if (weekIndex < 7) {
      for (let i = preMonthLastDay.getDate() - weekIndex + 1; i <= preMonthLastDay.getDate(); i++) {
        result.push({
          year: preMonthLastDay.getFullYear(),
          month: preMonthLastDay.getMonth() + 1,
          day: i,
          isCurMonth: false,
        });
      }
    }
    let curMonthLastDay = new Date(year, month + 1, 0);
    for (let i = 1; i <= curMonthLastDay.getDate(); i++) {
      result.push({
        year: curMonthLastDay.getFullYear(),
        month: curMonthLastDay.getMonth() + 1,
        day: i,
        isCurMonth: true,
      });
    }
    let lastDayCount = 42 - result.length;
    if (lastDayCount > 0) {
      let nextMonthLastDay = new Date(year, month + 2, 0);
      for (let i = 1; i <= lastDayCount; i++) {
        result.push({
          year: nextMonthLastDay.getFullYear(),
          month: nextMonthLastDay.getMonth() + 1,
          day: i,
          isCurMonth: false,
        });
      }
    }
    return result;
  }
  static timeStr(startTime: number) {
    let span = startTime - Date.now();
    if (span < 3600000) {
      //1个小时
      let min = Math.floor(span / 60000);
      if (min < 1) {
        return `马上`;
      }
      return `${min}分钟后`;
    } else if (span < 86400000) {
      //1天
      return `${Math.floor(span / 3600000)}小时后`;
    } else {
      let startObj = new Date(startTime);
      let now = new Date();
      if (startObj.getMonth() === now.getMonth() && startObj.getFullYear() === now.getFullYear()) {
        return `${startObj.getDate() - now.getDate()}天后`;
      } else if (startObj.getFullYear() === now.getFullYear()) {
        return `${(startObj.getMonth() + 1).toString().padStart(2, "0")}月${startObj.getDate().toString().padStart(2, "0")}日`;
      } else {
        return `${startObj.getFullYear()}-${(startObj.getMonth() + 1).toString().padStart(2, "0")}-${startObj.getDate().toString().padStart(2, "0")}`;
      }
    }
  }
  static async jobDbClick(e: MouseEvent) {
    let id = (e.currentTarget as HTMLElement).dataset.id;
    let proxy = await horse.createWin({
      resizable: false,
      maximizable: false,
      minimizable: false,
      alwaysOnTop: false,
      skipTaskbar: false,
      visible: true,
      frame: false,
      shadow: true,
      title: "修改日程",
      size: {
        w: 800,
        h: 600,
      },
      minSize: {
        w: 250,
        h: 200,
      },
      pos: "centerScreen",
      url: `http://localhost:8000/IndexJob.html?editId=${id}`,
    });

    Helper.$id("ModalMask").style.display = "block";
  }
  static jobMouseDown(e: MouseEvent) {
    e.preventDefault();
    e.stopPropagation();
    if (e.button === 0) {
      let target = e.currentTarget as HTMLElement;
      let dateObj = new Date(parseInt(target.dataset.start));
      let event = new CustomEvent("gotodateview", { detail: dateObj });
      Helper.$id("SwitchBtns").dispatchEvent(event);
    } else {
      Helper.showJobMenu(e);
    }
    return true;
  }
  static clickNum: number = 0;
  static clickTimer;
  static jobItemMouseDown(e: MouseEvent) {
    if (e.button === 0) {
      Helper.clickNum += 1;
      if (Helper.clickNum === 1) {
        let target = e.currentTarget as HTMLElement;
        let dateObj = new Date(parseInt(target.dataset.start));
        Helper.clickTimer = setTimeout(() => {
          Helper.clickNum = 0;
          let event = new CustomEvent("gotodateview", { detail: dateObj });
          Helper.$id("SwitchBtns").dispatchEvent(event);
        }, 260);
      } else if (Helper.clickNum === 2) {
        clearTimeout(Helper.clickTimer);
        Helper.clickNum = 0;
        this.jobDbClick(e);
      }
    } else {
      Helper.showJobMenu(e);
    }
  }
  static getGUID() {
    //@ts-ignore
    return ([1e7] + -1e3 + -4e3 + -8e3 + -1e11).replace(/[018]/g, (c) => (c ^ (crypto.getRandomValues(new Uint8Array(1))[0] & (15 >> (c / 4)))).toString(16));
  }
}
