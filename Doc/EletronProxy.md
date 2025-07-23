Chromium底层并不支持基于身份验证的代理（Socks5）方案

所以Electron也没提供支持

要解决这个问题，我最先想到的是Clash

然而clash和clash for windows的作者都删库跑路了，据说被国安的人喝茶了

我从昨晚到现在都没找到一个合适的替代方案

我看可能最合适的方案就是使用`游戏加速`那套方案了，

这方面我没搞过，去查了查资料

发现他们大都是使用SStap这个软件来加速游戏的

然而这个软件也停更了

https://github.com/FQrabbit/SSTap-Rule

（这里是一个网友整理的一些资料）

**不过总体思路都是一样的：**

1. 找到一款合适的代理软件。
2. 为这款代理软件配置好代理策略（包括代理的身份认真信息）
3. 把这个软件和其相关的配置集成到产品中。
4. 当用户启动产品时，使用child_process启动此代理软件
5. 当应用退出时，结束child_process进程

下面是示例代码：

```js
  let spawn = require("child_process").spawn;
  let child = spawn("proxy.exe", [], {
    cwd: "/proxy/path",
  });
  child.stdout.on("data", (data) => {
    console.log(data.toString("utf8"));
  });
  child.stdout.on("error", (data) => {
    console.log(data.toString("utf8"));
  });
  child.on("close", () => {
    //代理已退出。
  });
  child.exit();
```