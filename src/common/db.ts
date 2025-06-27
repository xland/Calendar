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
          return new Worker(new URL("sqlite3-worker1-bundler-friendly.mjs", "http://localhost:8000"), {
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
    debugger;
    await this.promiser("exec", {
      dbId: this.id,
      sql: "INSERT INTO t(a,b) VALUES (?,?)",
      bind: [1, 1 * 2],
    });
  }
}
export let db = new Db();
