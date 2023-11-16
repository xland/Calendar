# 脚踏esbuild祥云，胸怀tsx利刃，身披scss羽衣，追寻前端的本质

> 本文所有内容，纯属个人观点，无意与任何人争论

## 前端技术的现状

我觉得前端技术发展到现在有两个最主要的特征

1. 前端工具链为前端工程化提供了强有力的支持

> 这方面主要是`webpack`、`rollup`、`esbuild`等工具产生的价值，当然还有背后的`Node.js`。
> 
> 这些工具让前端开发者可以更从容的开发大型前端项目。

2. 前端开发框架提升了前端工程师的生产效率

> 这方面主要是`Angular`、`React`、`Vue`和`Svelte`等开发框架产生的价值。
> 
> 这些框架让开发者可以更容易的开发前端项目

前端工具链的价值毋庸置疑，但前端开发框架的价值与影响值得讨论。

前端开发框架之所以能提升前端工程师的生产效率，是因为它为我们做了大量的封装。

这种封装工作在提升生产效率的同时也带来了复杂性，甚至有些封装工作的复杂程度远超了业务逻辑本身。

比如：我们修改一个变量的值，并把这个值更新到Dom中，

在不使用前端框架时，我们一般会写这样的代码
```js
let count = 0
count + = 1;
let dom = document.getElementById("id")
dom.innerHTML = count
```
使用前端框架后，写的代码变成了这样：
```js
// Vue
// <div>{{count}}</div>
let count = ref(0)
count.value += 1
```
```js
// React
// <div>{count}</div>
const [count, setCount] = useState(0);
setCount(count + 1);
```
```js
// Svelte
// <div>{count}</div>
let count = 0;
count += 1;
```
如你所见，前端开发框架帮开发者做了大量的工作，比如：虚拟DOM，Diff算法，代理观察变化等等。

大有 `为了一碟醋，包了一锅饺子` 的嫌疑，就算这锅饺子是尤雨溪帮我们包的，

我们也很难说饺子馅里油多了还是油少了，饺子皮是高筋面粉还是低筋面粉。

甚至现在大家都不考虑自己的身子适不适合吃饺子了，既然是尤雨溪帮我包的，那我一定要吃呀！

当我们的页面变卡、页面占用的内存逐渐上升最后OOM时，

我们有考虑过，如果不用这些框架，是不是这类问题更容易被发现，更容易被控制呢？

（当然，这里提到的问题，一定是我们吃饺子的姿势不对导致的，不是饺子本身的问题^_^）

## 回归前端的本质

我们要回到前端开发者刀耕火种、茹毛饮血的时代吗？当然不是。

那么哪些东西是我们不想放弃的？

1. 组件化开发的模式

> 标题栏一个组件，侧边栏一个组件，菜单一个组件，各个组件有各个组件各自的业务逻辑。

2. 困扎代码

> 发布之前，各个组件的代码会被困扎到一起，产出很多个chunk文件，`tree-shake`会帮我们移除没用到的代码

3. 热更新或热重载的能力

> 改了某个组件的代码，能实时看到改动后的结果，如果达不到热更新，那就保留最基本的热重载能力。

4. 样式隔离

> 不一定要Shadow Dom，我们可以制定一套规则来约束组件的样式。

5. 强类型与智能提示
   
> 最好有`TypeScript`的强类型支持，写组件的时候最好能有足够多的智能提示

除了这些东西之外，

像虚拟Dom，Diff算法，Watch对象的变化，组件间通信，数据绑定等，

我们都可以抛弃，这些本来就是我们自己的工作，不需要框架来帮我们做。

归根结底：**在写代码的时候，我们要始终知道自己在做什么**。

## 方案

1. 基于 `Web Component` 技术与相关的辅助工具

> 单纯用 Web Component 开发的话，挺麻烦的。
> 
> 要写一个工具才才能提升我们使用这个方案的开发体验，
> 
> 比如把`template`、`css样式`和`代码文件`封装到一个单独的组件中
> 
> 搞定这个工具没那么容易，而且搞不好又回到了老路上，等于自己开发了一个前端框架，
> 
> 我在这个方向上做过一些尝试，后来就放弃了

2. 基于 `JSX/TSX` 技术及相关辅助工具

> 现在`VSCode`对`JSX/TSX`语法支持的很好，esbuild也内置支持对`JSX/TSX`的困扎
>
> 最关键的是：实现一个简单的`JSX/TSX`解析器非常容易（不依赖React库）

## JSX/TSX解析器

废话不多说，直接看解析器的代码吧：

```ts
// React.ts
let appendChild = (children: any,node: Node)=> {
    if (Array.isArray(children)) {
        for (const child of children) {
            if(child) appendChild(child,node)
        }
    } else if (typeof children === "string" || typeof children === "number") {
        let textNode = document.createTextNode(children as any)
        node.appendChild(textNode)
    } else if (typeof children.nodeType === "number") {
        node.appendChild(children)
    }
}
let appendAttr = (attr: object,node: HTMLElement)=>{
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
        }        
        else {
            node.setAttribute(key, val)
        }
    }
}
let createElement = (tag: any, attr: any, ...children: any[]) => {
    if(typeof tag === "string"){
        let node = document.createElement(tag);
        if(attr) appendAttr(attr,node)
        if(children) appendChild(children,node)
        return node;
    } else if(typeof tag === "function"){
        let obj = tag({...attr,children})
        return obj
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
```

没错，就这么4个简单的方法，就能解析大部分`JSX/TSX`语法

> 像在`JSX/TSX`中使用SVG这类需求，我就直接忽略了，遇到这类需求用原始的HTML方法处理最好

下面是一个简单的示例

```tsx
import React from "./React"; 
let App = ()=>{
  let count = 1;
  return <div>{count}</div>
}
document.body.appendChild(<App/>);
```

这个组件的第一行导入了前面介绍的四个方法

注意：**这个组件中没有使用任何React对象的方法，也得导入React对象，而且必须叫React对象，不然esbuild不认。**

子组件示例

```tsx
//主组件  App.tsx
import React from "./React";
import LeftPanel from "./LeftPanel";
import MainPanel from "./MainPanel";
let App = ()=>{
  return <><LeftPanel/><MainPanel/></>
}
document.body.appendChild(<App/>);
```

```tsx
// 子组件  LeftPanel.tsx
import React from "./React"; 
export default function () {  
  let count = 1;
  return <div>{count}</div>
}
```

其他一些动态创建元素的方法也都支持，比如：

```jsx
//示例1
<div>
    {[...Array(8)].map((v,i)=><div>{`${i}`}</div>) }
</div>
```
```jsx
//示例2
let container = document.getElementById("container");
for(let i=0;i<6;i++){
    let row = <div class="row"></div>            
    for(let j=0;j<7;j++){
        let cell = <div><div class="cellHeader">{obj.content}</div></div>        
        row.appendChild(cell)
    }
    container.append(row)
}
```

## 用esbuild启动调试服务器

先来看脚本代码：

```ts
// ./script/dev.js
let esbuild = require("esbuild")
let {sassPlugin} = require("esbuild-sass-plugin")
let fs = require("fs")
let startDevServer = async ()=>{
    let content = `<html><head>
    <meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
    <link rel="stylesheet" href="./Index.css">
</head><body>
    <script src="./Index.js"></script>
    <script>
        new EventSource('/esbuild').addEventListener('change', () => location.reload())
    </script>
</body></html>`;
    await fs.writeFile(`./dist/Index.html`,content)
    let ctx = await esbuild.context({
      entryPoints: [`./Index.tsx`],
      bundle: true,
      outdir: 'dist',
      plugins: [sassPlugin()],
      sourcemap:true
    })  
    await ctx.watch()  
    let { host, port } = await ctx.serve({
      servedir: 'dist',
    })
    let devServerAddr = `http://localhost:${port}/index.html`
    console.log(devServerAddr)
  }
startDevServer();
```
有了这个脚本之后，你只要在package.json中加一行这样的指令

```
"dev": "node ./script/dev.js",
```
就可以通过这个命令行命令
```
npm run dev
```
启动你得调试页面了

如你所见，我们为esbuild增加了`esbuild-sass-plugin`插件，这样我们就可以在`tsx/jsx`组件中使用`scss`样式了
```
import "./Index.scss";
```
上面的模板html代码中有一行这样得脚本
```js
new EventSource('/esbuild').addEventListener('change', () => location.reload())
```
此脚本为`esbuild`的热重载服务，

当我们修改某个组件的代码时，`整个`页面会跟着刷新

> 这不是热更新，只是热重载，有它就够了，上热更新代价太大，就不要自行车了。

## esbuild 打包产物

先看代码
```js
// ./script/release.js
let esbuild = require("esbuild")
let {sassPlugin} = require("esbuild-sass-plugin")
let fs = require("fs")

let release = async ()=>{
    let content = `<html><head>
<meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
<link rel="stylesheet" href="./Index.css">
</head><body><script src="./Index.js"></script></body></html>`;
    await fs.writeFile(`./release/Index.html`,content)
    let ctx = await esbuild.build({
      entryPoints: [`./Index.tsx`],
      bundle: true,
      outdir: 'release',
      plugins: [sassPlugin()],
      minify: true,
      sourcemap:false
    })
    console.log("build ok")
    }
release();
```

package.json中加入：

```
"release": "node ./script/release.js"
```

打包指令：
```
npm run release
```

打包代码比较简单，关键点是`minify`设置为`true`以压缩输出产物。

## scss 隔离样式

假设我们约定一个组件的根元素有一个父样式，

这个父样式约束着这个组件的所有子元素得样式

那就可以用下面的代码，让组件的样式作用于组件内，不污染全局样式

```scss
//ViewDay.scss
#ViewDay{
    cursor: pointer;
    .bgLine{        
        //
    }
    #JobContainer{
        //
    }
}
```

```tsx
// 子组件  ViewDay.tsx
import React from "./React"; 
import "./ViewDay.scss";
export default function () {  
  return <div id="ViewDay">
    <div class="bgLine"></div>
    <div id="JobContainer"></div>
  </div>
}
```

这样 `.bgLine` 和 `#JobContainer` 就不会影响其他组件内的同名样式了
