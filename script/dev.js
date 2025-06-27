let esbuild = require("esbuild");
let { sassPlugin } = require("esbuild-sass-plugin");
let fs = require("fs-extra");
let statik = require("node-static");

let getTemplate = (item) => {
  let str = `<html><head><meta http-equiv="Content-Type" content="text/html;charset=UTF-8"><link rel="stylesheet" href="./res/iconfont.css">
<link rel="stylesheet" href="./${item}.css"></head><body class="blue"><script src="./${item}.js"></script></body></html>`;
  return str;
};

let startDevServer = async () => {
  let arr = ["Index", "IndexJob", "IndexAlert"];
  for (let item of arr) {
    let content = getTemplate(item);
    await fs.writeFile(`./dev/${item}.html`, content);
  }
  let ctx = await esbuild.context({
    entryPoints: arr.map((v) => `./src/${v}.tsx`),
    bundle: true,
    outdir: "dev",
    plugins: [sassPlugin()],
    platform: "browser",
    sourcemap: true,
    target: "esnext",
  });
  await ctx.watch();

  const file = new statik.Server("./dev");

  require("http")
    .createServer(function (request, response) {
      request
        .addListener("end", function () {
          response.appendHeader("Cross-Origin-Opener-Policy", "same-origin");
          response.appendHeader("Cross-Origin-Embedder-Policy", "require-corp");
          file.serve(request, response);
        })
        .resume();
    })
    .listen(8000);
};

// let initConfig = async () => {
//   let configStr = `{
//   "appId": "Calendar",
//   "instanceWatch": true,
//   "instanceLock": true,
//   "quitWhenAllWinClosed": true,
//   "window": {
//     "resizable": true,
//     "maximizable": true,
//     "minimizable": false,
//     "alwaysOnTop": false,
//     "skipTaskbar": false,
//     "visible": true,
//     "frame": false,
//     "shadow": true,
//     "title": "日历",
//     "size": {
//       "w": 1200,
//       "h": 800
//     },
//     "minSize": {
//       "w": 250,
//       "h": 200
//     },
//     "pos": "centerScreen",
//     "scriptDialogEnable": true,
//     "scriptEnable": true,
//     "webMessageEnable": true,
//     "contextMenuEnable": true,
//     "url": "${devServerAddr}"
// }}`;
//   await fs.writeFile(`./dev/UI/config.json`, configStr);
// };

let startHorseJs = async () => {
  let spawn = require("child_process").spawn;
  let child = spawn("../dev/HorseJs.exe", [], {
    cwd: "./dev",
  });
};

let start = async () => {
  await startDevServer();
  // await initConfig();
  // startHorseJs();
};
start();
