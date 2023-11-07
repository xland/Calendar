//胸怀tsx利刃，脚踏scss祥云，回归前端的本质
class Widget{
    props:any
    ready(){

    }
    render(){

    }
    constructor(){

    }
}

let isString = (val)=>typeof val === "string"
let isNumber = (val)=>typeof val === "number"

let createElement = (tag: any, attr: any, ...children: any[]) => {
    if(typeof tag === "string"){
        let node = document.createElement(tag);
        console.log(children)
        appendChild(children, node)
        return node;
    }
    let obj = new tag() as Widget
    return obj.render()
}

function appendChild(child: any,node: Node) {
    if (Array.isArray(child)) {
        for (const n of child) {
            appendChild(n, node)
          }
    } else if (isString(child) || isNumber(child)) {
        let textNode = document.createTextNode(child as any)
        node.appendChild(textNode)
    } else if (child === null) {
    //   appendChildToNode(document.createComment(""), node)
    }
  }




export default {
    createElement,
    Widget
}