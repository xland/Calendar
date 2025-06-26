interface Win {
  startDrag: () => {};
  on: (evtName: string, cb: (result: { state: string }) => void) => void;
  minimize: () => void;
  restore: () => void;
  maximize: () => void;
  close: () => void;
}
interface Db {
  open(dbPath: string, inDataPath?: boolean): { ok: boolean; isDbFirstCreated: boolean; data: string; err?: string };
}
interface Horse {
  win: Win;
  db: Db;
}
declare var horse: Horse;
