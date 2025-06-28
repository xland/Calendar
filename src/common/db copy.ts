import { Promiser, sqlite3Worker1Promiser } from "@sqlite.org/sqlite-wasm";
class Db {
  id: string;
  promiser: Promiser;
  constructor() {}
  async open() {
    this.promiser = await new Promise((resolve) => {
      const _promiser = sqlite3Worker1Promiser({
        worker: () => {
          let url = new URL(location.href);
          return new Worker(new URL("sqlite3-worker1-bundler-friendly.mjs", url.origin), {
            type: "module",
          });
        },
        onready: () => resolve(_promiser),
      });
    });
    const openResponse = await this.promiser("open", {
      filename: "file:db.sqlite3?vfs=opfs",
    });
    this.id = openResponse.dbId;
    await new Promise(async (resolve) => {
      await this.promiser("exec", {
        dbId: this.id,
        sql: `SELECT name FROM sqlite_master WHERE type='table' AND name='Job';`,
        callback: async (result) => {
          console.log(result.row);
          if (!result.row || result.row.length < 1) {
            await this.promiser("exec", {
              dbId: this.id,
              sql: ` CREATE TABLE Job(Id VARCHAR2(36) NOT NULL PRIMARY KEY, JobInfo TEXT, RepeatType INT, StartTime BIGINT, EndTime BIGINT, ColorIndex INT);
CREATE INDEX JobInfo_Index ON Job(JobInfo);
CREATE TABLE Setting(ViewDefault INT DEFAULT 0, ViewVal INT, LangDefault INT DEFAULT 0, SkinDefault INT DEFAULT 0, AlertBefore INT);
INSERT INTO Setting (ViewDefault, ViewVal, LangDefault, SkinDefault, AlertBefore)
VALUES (0, 0, 0, 0, 5);`,
            });
            console.log("init Db");
            resolve(null);
          } else {
            resolve(null);
          }
        },
      });
    });
    console.log("open db");
  }
}
export let db = new Db();
