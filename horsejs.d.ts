type BaseResult = {
  /**
   * 操作是否成功
   */
  ok: boolean;
  /**
   * 如果操作不成功，err将携带错误信息
   */
  err?: string;
};

type Result<T = void> = BaseResult & T;

/**
 * 窗口事件名称
 */
type WinEventName = "closing" | "stateChanged";

interface Win {
  /**
   * 关闭窗口Y
   */
  close(): Result;
  /**
   *鼠标按下，开始拖拽移动窗口的位置
   */
  startDrag(): Result;
  /**
   * 监听窗口事件
   * @param evtName 事件名称
   * @param cb 事件发生时的回调函数
   */
  on(
    evtName: WinEventName,
    cb: (result: {
      /**
       * 窗口状态
       */
      state: string;
    }) => void
  ): Result;
  /**
   * 取消监听事件
   * @param evtName
   * @param cb
   */
  off(
    evtName: WinEventName,
    cb?: (result: {
      /**
       * 窗口状态
       */
      state: string;
    }) => void
  ): Result;
  /**
   * 最小化窗口
   */
  minimize(): Result;
  /**
   * 还原窗口
   */
  restore(): Result;
  /**
   * 最大化窗口
   */
  maximize(): Result;
  /**
   * 关闭窗口
   * @returns
   */
  close(): Result;
}

interface Horse {
  win: Win;
  /**
   * 设置开机自启动
   * @param needAutoStart true为开机自启动，false为开机不启动
   */
  autoStart(needAutoStart: boolean);
  /**
   * 创建一个新窗口
   * @param config 窗口配置
   */
  createWin(config: object);
}
declare var horse: Horse;
