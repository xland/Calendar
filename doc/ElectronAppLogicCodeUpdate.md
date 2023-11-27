# 渲染进程界面逻辑非实时更新

对于渲染进程中非关键业务的代码逻辑来说，更新并没有及时性的要求，

只要把这部分代码（HTML/CSS/JS/Image/Font）放到服务器上，

当用户打开（或刷新）应用的浏览器容器组件时，

BrowserWindow/BrowserView/webview会自动加载这部分代码。

需要更新这部分代码时，只要把新代码文件覆盖掉服务器上的对应文件

当用户重新打开（或刷新）BrowserWindow/BrowserView/webview时

用户就会得到更新后的代码逻辑。

**注意事项（缓存）：**

应该考虑客户端缓存导致代码文件无法更新的问题，

最常见且有效的办法就是加载资源时加上一个随机数参数：

`src="https://domain.com/logic.js?rnd=9632587410"`

除此之外，可以协调服务端开发人员设置服务端的强制缓存或协商缓存

如果以上两种手段均难以实施，可以考虑使用以下代码禁用缓存：

```js
const dbg = win.webContents.debugger
dbg.attach()
await dbg.sendCommand('Network.enable')
await dbg.sendCommand('Network.setCacheDisabled',{cacheDisabled:true})
```

**总结：**

这类更新取决于用户的行为，如果用户不重启（或刷新）BrowserWindow/BrowserView/webview，那么新代码逻辑就不会传递给用户。

## 渲染进程界面逻辑准实时更新

对于渲染进程的核心逻辑代码来说，更新的及时性要求较高，

这类更新不能依赖于用户的行为，应用程序最好有能力主动更新这部分业务逻辑

此时可以考虑在服务端设置一个长连接服务（比如：WebSocket接口）

> 也可以在客户端设置定时器轮询服务端接口，判断服务端是否存在新版本的代码文件，
> 
> 但这样会产生较多无效请求（长连接会占用较多客户端和服务端资源），具体选哪个方案，还得根据具体情况确定

当我们更新服务器上的代码文件之后，

服务端通过此长连接向所有在线的客户端下发通知，要求客户端更新此部分业务逻辑

> 不在线的客户端会在下次启动后更新这部分逻辑

客户端收到服务端的通知之后，

只要强制刷新BrowserWindow/BrowserView/webview即可得到新代码的业务逻辑

> 视业务情况决定是否给用户提示

**注意事项：**

这部分代码也是放在服务器上的HTML/CSS/JS/Image/Font代码文件

这种更新方式并不能更新客户端asar文件中的代码。

# 渲染进程第三方代码Hack更新

假设Electron应用加载了第三方页面，且第三方页面的代码逻辑不符合我们的预期，

而第三方代码部署在第三方的服务器上，我们无权修改，

再加上浏览器同源策略的限制，导致更新第三方代码逻辑困难重重

此时可以考虑使用如下方式，重定向第三方页面的关键请求

以达到修改第三方页面关键代码的目的

且这种方式可以绕过同源策略的限制

```js
win.webContents.session.webRequest.onBeforeRequest({ urls: ["https://*/*"] }, async (details, cb) => {
            if (details.url === 'https://target.domain.com/target.js') {
                cb({ redirectURL: 'http://your.domain.com/your.js' });
            } else {
                cb({})
            }
        });
```

在Electron应用内，我们同样有能力修改第三方页面的Cookie

```js
win.webContents.session.cookies.on('changed', async (e, cookie, cacuse, removed) => {
            if (cookie.session && !removed) {
                let domain = cookie.domain.startsWith('.') ? cookie.domain.substr(1) : cookie.domain;
                let url = `${cookie.secure ? 'https' : 'http'}://${domain}${cookie.path}`;
                let obj = {
                    url: url,
                    name: cookie.name,
                    value: cookie.value,
                    domain: cookie.domain,
                    path: cookie.path,
                    secure: cookie.secure,
                    httpOnly: cookie.httpOnly,
                    expirationDate: Math.floor(Date.now() / 1000) + this.day80
                };
                await this.win.webContents.session.cookies.set(obj);
            }
        });
```

# 更新asar文件

一个Electron应用，大部分逻辑都被保存在asar文件中

`installPath/resources/app.asar`

所以如果只是升级应用程序的逻辑代码，只要升级此文件即可，没必要更新整个Electron框架

为了达到这个目的，

我们先看以下打包到asar中的package.json文件：

```json
{
  "name": "appname",
  "version": "1.1.1",
  "private": true,
  "main": "entry.js"
}
```

这是整个应用程序的配置文件，据此配置，当Electron应用启动时，先执行asar文件中的entry.js文件

下面时entry.js的核心逻辑

```js
//entry.ts
import { app } from "electron"
import fsPromises from 'fs/promises'
import os from 'os'
import path from 'path'
let mainFolder = path.join(app.getPath("userData"), 'main')
let fileList = await fsPromises.readdir(mainFolder)
let mainPath;
if (fileList.length <= 0){
    mainPath = path.join(__dirname, 'main.js')
}else{
    mainPath = path.join(mainFolder, `new-version.asar`, 'main.js')
}
let main = require(this.mainPath)
main.start()
```

这段代码会判断用户userData是否存在新版本的asar文件

> C:\Users\liuxiaolun\AppData\Roaming\appName\main\new-version.asar

如果不存在，则加载安装目录下的asar文件中的main.js

> C:\Program Files\appName\resources\app.asar

如果存在，则加载userData目录下asar文件中的main.js

main.js文件则承载着应用程序主进程的业务逻辑，示例代码如下所示：

```js
//main.ts
class Main {
    mainWindow:BrowserWindow;
    start() {
        mainWindow = new BrowserWindow(options);
    }
}
let main = new Main()
module.exports = main
```

用户首次安装应用程序时，userData目录下不会存在任何asar文件

所以一定会加载安装目录下app.asar中的main.js

当我们打算升级应用程序逻辑时，

会编译一个新的asar文件，并发布到服务器上

应用程序检测到服务器上存在新版本的asar文件后，会下载到用户的userData目录中

此时可以提示用户重启应用

当用户重启应用后，entry.js会加载userData目录下asar文件中的main.js

这就是Electron应用仅更新asar文件的方式。

**注意事项（版本控制）：**

上面的关键代码中并未兼顾asar文件的版本控制，

实际情况用户userData目录下可能会存在多个asar文件，

我们应该根据版本号命名规则加载最新的asar文件

# 应用程序升级

`electron-updater`允许开发者把安装包提前下载到用户的缓存目录下

```ts
let macPath = path.join(app.getPath('appData'), `Application Support/Caches/appName-updater/pending`)
let winPath = path.join(app.getPath('appData'), `Local/appName-updater/pending`)
```

下载完成后即可提醒用户，重启应用安装新版本

```ts
import { autoUpdater } from 'electron-updater'
autoUpdater.quitAndInstall()
```