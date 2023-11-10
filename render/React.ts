//脚踏esbuild祥云，胸怀tsx利刃，身披scss羽衣，追寻前端的本质

let appendChild = (children: any,node: Node)=> {
    if (Array.isArray(children)) {
        for (const c of children) {
            appendChild(c,node)
          }
    } else if (typeof children === "string" || typeof children === "number") {
        let textNode = document.createTextNode(children as any)
        node.appendChild(textNode)
    } else if (children === null) {
        console.log("child null error",children)
        //   appendChildToNode(document.createComment(""), node)
    } else if (typeof children.nodeType === "number") {
        node.appendChild(children)
      }
}
let appendAttr = (attr: object,node: HTMLElement)=>{
    if(!attr) return node;
    for (let key of Object.keys(attr)) {
        let val = attr[key];
        if(key === "style"){
            node.setAttribute("style", val)
        } else if(typeof val === "function"){
            if(key.startsWith("on")){
                node.addEventListener(key.toLocaleLowerCase().substring(2), val)
            }
        } else if(typeof val === "object"){
            node[key] = val
            console.log("allen",node,key)
        }        
        else {
            node.setAttribute(key, val)
        }
    }
    return node
}
let createElement = (tag: any, attr: any, ...children: any[]) => {
    console.log(tag)
    if(typeof tag === "string"){
        let node = document.createElement(tag);
        if(attr) appendAttr(attr,node)
        if(children) appendChild(children,node)
        return node;
    } else if(typeof tag === "function"){
        let obj = tag({...attr,children})
        return obj
    }else {
        console.log(tag,attr,children)
    }    
}
let Fragment = (attr:any) =>{
    const fragment = document.createDocumentFragment()
    appendChild(attr.children, fragment)
    return fragment
  }

export default {
    createElement,
    Fragment
}