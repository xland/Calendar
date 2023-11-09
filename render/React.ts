//脚踏esbuild祥云，胸怀tsx利刃，身披scss羽衣，追寻前端的本真

let isString = (val)=>typeof val === "string"
let isNumber = (val)=>typeof val === "number"
let isElement = (val)=>val && typeof val.nodeType === "number"
let isFunction = (val)=>val && typeof val === "function"

let appendChild = (child: any,node: Node)=> {
    if (Array.isArray(child)) {
        for (const c of child) {
            appendChild(c,node)
          }
    } else if (isString(child) || isNumber(child)) {
        let textNode = document.createTextNode(child as any)
        node.appendChild(textNode)
    } else if (child === null) {
        console.log("child null error",child)
        //   appendChildToNode(document.createComment(""), node)
    }
    else if (isElement(child)) {
        node.appendChild(child)
      }
}

let appendAttr = (attr: object,node: HTMLElement)=>{
    if(!attr) return node;
    for (let key of Object.keys(attr)) {
        let val = attr[key];
        if(key === "style"){
            node.setAttribute("style", val)
        }
        if(isFunction(val)){
            if(key.startsWith("on")){
                node.addEventListener(key.toLocaleLowerCase().substring(2), val)
            }
        }
        console.log(key,"--", attr[key], node)
    }
    return node
}

let createElement = (tag: any, attr: any, ...children: any[]) => {
    if(typeof tag === "string"){
        let node = document.createElement(tag);
        appendAttr(attr,node)
        appendChild(children,node)
        return node;
    }
    let obj = tag({...attr,children})
    return obj
}






export default {
    createElement
}