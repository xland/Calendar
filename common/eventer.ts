type EventHandler = (result: any) => void;
export class Eventer {
  private dic = {};
  constructor() {}
  // 监听事件
  on(eventName: string, cb: EventHandler) {
    if (!this.dic[eventName]) {
      this.dic[eventName] = [cb];
      return true;
    } else {
      this.dic[eventName].push(cb);
      return false;
    }
  }
  has(eventName: string) {
    return this.dic[eventName] && this.dic[eventName].length > 0;
  }
  // 取消监听事件
  off(eventName: string, cb?: EventHandler) {
    const handlers = this.dic[eventName];
    if (!handlers) return false;
    if (cb) {
      const index = handlers.findIndex((h) => h === cb);
      if (index >= 0) handlers.splice(index, 1);
    }
    if (handlers.length === 0 || !cb) {
      delete this.dic[eventName];
      return true;
    }
    return false;
  }
  // 发射事件
  emit(eventName: string, result?: any): void {
    const handlers = this.dic[eventName];
    if (!handlers || handlers.length === 0) {
      console.warn(`no call back：${eventName}`);
      return;
    }
    handlers.forEach((handler) => {
      handler(result);
    });
  }

  // 监听一次性事件
  once(eventName: string, cb: EventHandler): void {
    const wrapper = (result: any) => {
      this.off(eventName, wrapper);
      cb(result);
    };
    this.on(eventName, wrapper);
  }
}
export let eventer = new Eventer();
