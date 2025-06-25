interface Win {
  startDrag: () => {};
}
interface Horse {
  win: Win;
}
declare var horse: Horse;

declare global {
  interface HTMLElement {
    prev(): HTMLElement;
    next(): HTMLElement;
    son0(): HTMLElement;
    son1(): HTMLElement;
    dad(): HTMLElement;
    classAdd(name: string);
    classDel(name: string);
    classHas(name: string): boolean;
  }
}
