let esbuild = require("esbuild");
let { sassPlugin } = require("esbuild-sass-plugin");
let fs = require("fs-extra");

let getTemplate = (item) => {
  let devScriptStr = `<script>new EventSource('/esbuild').addEventListener('change', () => location.reload())</script>`;
  let str = `<html><head><meta http-equiv="Content-Type" content="text/html;charset=UTF-8"><link rel="stylesheet" href="./res/iconfont.css">
<link rel="stylesheet" href="./${item}.css"></head><body class="blue"><script src="./${item}.js"></script>${devScriptStr}</body></html>`;
  return str;
};

let startDevServer = async () => {
  let arr = ["Index", "IndexJob", "IndexAlert"];
  for (let item of arr) {
    let content = getTemplate(item);
    await fs.writeFile(`./dev/${item}.html`, content);
  }
  let ctx = await esbuild.context({
    entryPoints: arr.map((v) => `./render/${v}.tsx`),
    bundle: true,
    outdir: "dev",
    plugins: [sassPlugin()],
    platform: "browser",
    sourcemap: true,
    target: "esnext",
  });
  await ctx.watch();
  let { port } = await ctx.serve({
    servedir: "dev",
  });
  devServerAddr = `http://localhost:${port}/index.html`;
  console.log(devServerAddr);
};
let start = async () => {
  await startDevServer();
};
start();
