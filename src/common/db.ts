class Db {
  constructor() {}
  log(...args) {
    console.log(args.join(" ") + "\n");
  }
  error(...args) {
    console.error("ERROR: " + args.join(" ") + "\n");
  }
  async open() {
    this.log("Loading and initializing SQLite3 module...");
    const promiser = await new Promise((resolve) => {
      const _promiser = sqlite3Worker1Promiser({
        onready: () => resolve(_promiser),
      });
    });
    this.log("Done initializing. Running demo...");

    // Get SQLite version
    const configResponse = await promiser("config-get", {});
    this.log("Running SQLite3 version", configResponse.result.version.libVersion);

    // Open a database with OPFS
    const openResponse = await promiser("open", {
      filename: "file:mydb.sqlite3?vfs=opfs",
    });
    const { dbId } = openResponse;
    this.log("OPFS database created at", openResponse.result.filename.replace(/^file:(.*?)\?vfs=opfs$/, "$1"));

    // Create a table
    await promiser("exec", {
      dbId,
      sql: "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, age INTEGER)",
    });
    this.log("Created users table.");

    // Insert data
    await promiser("exec", {
      dbId,
      sql: "INSERT INTO users (name, age) VALUES (?, ?)",
      bind: ["Alice", 30],
    });
    await promiser("exec", {
      dbId,
      sql: "INSERT INTO users (name, age) VALUES (?, ?)",
      bind: ["Bob", 25],
    });
    this.log("Inserted sample data.");

    // Query data
    const queryResponse = await promiser("exec", {
      dbId,
      sql: "SELECT * FROM users ORDER BY id",
      returnValue: "resultRows",
      rowMode: "object",
    });
    this.log("Query results:", JSON.stringify(queryResponse, null, 2));

    // Close the database
    await promiser("close", { dbId });
    this.log("Database closed.");
  }
}
export let db = new Db();
