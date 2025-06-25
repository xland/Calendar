interface Win {
  startDrag: () => {};
  on: (evtName: string, cb: (result: { state: string }) => void) => void;
  minimize: () => void;
  restore: () => void;
  maximize: () => void;
  close: () => void;
}
interface Horse {
  win: Win;
}
declare var horse: Horse;
