export {};

declare global {
    interface HTMLElement {
        prev(): HTMLElement;
        next(): HTMLElement;
        son0(): HTMLElement;
        son1(): HTMLElement;
        dad():HTMLElement;
    }
}

