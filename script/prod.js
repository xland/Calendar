let esbuild = require("esbuild")
let {sassPlugin} = require("esbuild-sass-plugin")
let fs = require("fs-extra")

let buildMain = async ()=>{
  await fs.copy("./build/","./prod/build/")
  await esbuild.build({
    entryPoints: ['./main/index.ts'],
    bundle: true,
    outfile:"./prod/main.js",
    platform:"node",
    external:["electron"],
    minify: true,
    sourcemap:false
  }) 
}

let buildRender = async ()=>{
  await fs.copy("./dev/res/","./prod/res")
  let arr = ["Index","IndexJob","IndexAlert"];
  for(let item of arr){
    let content = `<html><head><meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
<link rel="stylesheet" href="./${item}.css"></head><body><script src="./${item}.js"></script></body></html>`;
    await fs.writeFile(`./prod/${item}.html`,content)
  }
  await esbuild.build({
      entryPoints: arr.map(v=> `./render/${v}.tsx`),
      bundle: true,
      outdir: 'prod',
      plugins: [sassPlugin()],
      platform:"node",
      external:["electron"],
      minify: true,
      sourcemap:false
    })
    console.log("build ok")
}
buildMain()
buildRender();