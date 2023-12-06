let esbuild = require("esbuild")
let {sassPlugin} = require("esbuild-sass-plugin")
let fs = require("fs-extra")
let devServerAddr = "";

/**
 * 编译主进程代码
 */
let buildMain = async ()=>{
    await esbuild.build({
      entryPoints: ['./main/entry.ts'],
      bundle: true,
      outfile:"./dev/main.js",
      platform:"node",
      external:["electron"],
      sourcemap:true
    }) 
  }
/**
 * 启动Dev服务器
 */
let startDevServer = async ()=>{
  let arr = ["Index","IndexJob","IndexAlert"];
  for(let item of arr){
    let content = `<html><head>
    <meta http-equiv="Content-Type" content="text/html;charset=UTF-8">        
    <link rel="stylesheet" href="./res/iconfont.css">
    <link rel="stylesheet" href="./${item}.css">
</head><body>
    <script src="./${item}.js"></script>
    <script>
        new EventSource('/esbuild').addEventListener('change', () => location.reload())
    </script>
</body></html>`;
    await fs.writeFile(`./dev/${item}.html`,content)
  }
    let ctx = await esbuild.context({
      entryPoints: arr.map(v=> `./render/${v}.tsx`),
      bundle: true,
      outdir: 'dev',
      external:["electron"],
      plugins: [sassPlugin()],
      platform:"node",
      sourcemap:true
    })  
    await ctx.watch()  
    let { port } = await ctx.serve({
      servedir: 'dev',
    })
    devServerAddr = `http://localhost:${port}/index.html`
  }

/**
 * 启动Electron
 */
let startElectron = async ()=>{
    let electron = require("electron")
    let spawn = require("child_process").spawn;
    let child = spawn(electron,["./main.js",devServerAddr],{
        cwd:"./dev"
    })
    child.stdout.on('data', (data) => {
        console.log(data.toString("utf8"));
    });
    child.stdout.on('error', (data) => {
        console.log(data.toString("utf8"));
    });
    child.on("close", () => {
        process.exit();
      });
}
let startElectron2 = async ()=>{
  let electron = require("electron")
  let spawn = require("child_process").spawn;
  let child = spawn(electron,["./main.js"],{
      cwd:"./dist/win-unpacked/resources/app"
  })
  child.stdout.on('data', (data) => {
      console.log(data.toString("utf8"));
  });
  child.stdout.on('error', (data) => {
      console.log(data.toString("utf8"));
  });
  child.on("close", () => {
      process.exit();
    });
}
/**
 * 开始编译
 */
let start = async ()=>{
    await buildMain();
    await startDevServer();
    await startElectron();
    // await startElectron2();
}

start();