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

type WinEventName = "closing" | "stateChanged";

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
    evtName: WinEventName,
    cb: (result: {
      /**
       * 窗口状态
       */
      state: string;
    }) => void
  ): Result;
  off(
    evtName: WinEventName,
    cb?: (result: {
      /**
       * 窗口状态
       */
      state: string;
    }) => void
  ): Result;
  minimize(): Result;
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
interface Db {
  /**
   * 打开数据库
   * 第一个参数为数据库路径，可以是相对路径，也可以是绝对路径：
   *
   * 如果第一个参数为相对路径，且第二个参数的值为 true 则相对路径是应用程序数据目录的相对路径，比如：
   * C:\Users\liuxiaolun\AppData\Roaming\HorseJs\db.db
   *
   * 如果第一个参数为相对路径，且第二个参数的值为 false 则相对路径是应用程序 exe 文件所在目录的相对路径
   *
   * 第二个参数默认值为 true
   *
   * 如果第一个参数为相对路径，且第二个参数的值为 false ，返回值会返回创建的数据库的绝对路径。
   * @param dbPath 数据库路径
   * @param inDataPath 是否在应用程序数据目录中
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
  /**
   * 执行SQL语句
   * 允许一次性传入多条SQL指令，中间以分号分隔
   * @param sql SQL指令
   * @param dbPath 数据库路径
   */
  sql(
    sql: string,
    dbPath: string
  ): Result<{
    /**
     * 返回的数据
     */
    data: [any];
  }>;
}
interface Horse {
  win: Win;
  db: Db;
  autoStart(needAutoStart: boolean);
  createWin(config: object);
}
declare var horse: Horse;
