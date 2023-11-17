import EventEmitter from "events"
class Eventer extends EventEmitter {}
export let eventer = new Eventer();
