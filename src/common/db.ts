class Db {
  dbId: string;
  dbFunc: (cmd: string, param: object) => Promise<{ dbId: string; messageId: string; type: string; result: any }>;
  constructor() {}
  exec(sql: string): Promise<any[]> {
    return new Promise((resolve, reject) => {
      let rows = [];
      this.dbFunc("exec", {
        dbId: this.dbId,
        sql,
        callback: (result: { columnNames: string[]; row: any[]; rowNumber: number; type: string }) => {
          if (result.row) {
            let obj = {};
            for (let i = 0; i < result.columnNames.length; i++) {
              obj[result.columnNames[i]] = result.row[i];
            }
            rows.push(obj);
          } else {
            resolve(rows);
          }
        },
      });
    });
  }
  async open() {
    const dbFactory = globalThis.sqlite3Worker1Promiser.v2;
    delete globalThis.sqlite3Worker1Promiser;
    const config = {
      debug: (...args) => console.debug("db worker debug", ...args),
      onunhandled: (ev) => console.error("Unhandled db worker message:", ev.data),
      onerror: (ev) => console.error("db worker error:", ev),
    };
    this.dbFunc = await dbFactory(config);
    let { dbId } = await this.dbFunc("open", {
      filename: "file:db.sqlite3?vfs=opfs",
      simulateError: 0,
    });
    this.dbId = dbId;
    let rows = await this.exec(`SELECT name FROM sqlite_master WHERE type='table' AND name='Job';`);
    if (rows.length <= 0) {
      await this.exec(`CREATE TABLE Job(Id VARCHAR2(36) NOT NULL PRIMARY KEY, JobInfo TEXT, RepeatType INT, StartTime BIGINT, EndTime BIGINT, ColorIndex INT);
CREATE INDEX JobInfo_Index ON Job(JobInfo);
CREATE TABLE Setting(ViewDefault INT DEFAULT 0, ViewVal INT, LangDefault INT DEFAULT 0, SkinDefault INT DEFAULT 0, AlertBefore INT);
INSERT INTO Setting (ViewDefault, ViewVal, LangDefault, SkinDefault, AlertBefore) VALUES (0, 0, 0, 0, 5);`);
    }
    // let data = await this.exec(`select * from Setting;`);
    // console.log(data);
  }
  async delDb() {
    const opfsRoot = await navigator.storage.getDirectory();
    await opfsRoot.removeEntry("db.sqlite3");
  }
}
export let db = new Db();
