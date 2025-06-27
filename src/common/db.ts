import { Promiser, sqlite3Worker1Promiser } from "@sqlite.org/sqlite-wasm";
class Db {
  id: string;
  promiser: Promiser;
  constructor() {}
  async open() {
    debugger;
    this.promiser = await new Promise((resolve) => {
      const _promiser = sqlite3Worker1Promiser({
        worker: () => {
          let url = new URL(location.href);
          debugger;
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
    await this.promiser("exec", {
      dbId: this.id,
      sql: `CREATE TABLE Job(Id VARCHAR2(36) NOT NULL ON CONFLICT FAIL UNIQUE ON CONFLICT FAIL,JobInfo TEXT,RepeatType INT,StartTime BIGINT,EndTime BIGINT,ColorIndex INT);
CREATE INDEX JobInfo_Index ON Job(JobInfo);
CREATE TABLE Setting(ViewDefault INT DEFAULT 0,ViewVal Int,LangDefault INT DEFAULT 0,SkinDefault INT DEFAULT 0,AlertBefore INT);
INSERT INTO Setting (ViewDefault,ViewVal,LangDefault,SkinDefault,AlertBefore) VALUES (0,0,0,0,5);`,
    });
  }
}
export let db = new Db();
