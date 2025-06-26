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

type WinEventName = "maximize" | "minimize" | "close"; //todo

interface Win {
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
    evtName: string,
    cb: (result: {
      /**
       * 窗口状态
       */
      state: string;
    }) => void
  ): Result;
  minimize(): Result;
  restore(): Result;
  /**
   *
   */
  maximize(): Result;
  /**
   * 关闭窗口
   * @returns
   */
  close(): Result;
}
interface Db {
  /**
   *
   * @param dbPath
   * @param inDataPath
   */
  open(
    dbPath: string,
    inDataPath?: boolean
  ): Result<{
    /**
     * 是否第一次创建数据库
     */
    isDbFirstCreated: boolean;
    data: string;
  }>;

  sql(sql: string, dbPath?: string): Result;
}
interface Horse {
  win: Win;
  db: Db;
}
declare var horse: Horse;
