let esbuild = require("esbuild")
let {sassPlugin} = require("esbuild-sass-plugin")
let fs = require("fs-extra")
let start = async ()=>{
    esbuild.buildSync({
        entryPoints: ['./main/index.ts'],
        bundle: true,
        outfile:"./dist/main.js",
        platform:"node",
        external:["electron"],
        sourcemap:true
      })
    let arr = ["Index","IndexJob"];
    for(let item of arr){
        let content = `<html><head><meta http-equiv="Content-Type" content="text/html;charset=UTF-8">        
<link rel="stylesheet" href="./res/iconfont.css"><link rel="stylesheet" href="./${item}.css">
</head><body><script src="./${item}.js"></script></body></html>`;
        await fs.writeFile(`./dist/${item}.html`,content)
    }
    esbuild.build({
        entryPoints: [`./render/Index.tsx`],
        bundle: true,
        outdir: 'dist',
        plugins: [sassPlugin()],
        platform:"node",
        external:["electron"],
        sourcemap:true
      })
}
start();