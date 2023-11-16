let esbuild = require("esbuild")
let {sassPlugin} = require("esbuild-sass-plugin")
let fs = require("fs-extra")

let release = async ()=>{
    let content = `<html><head>
<meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
<link rel="stylesheet" href="./Index.css">
</head><body><script src="./Index.js"></script></body></html>`;
    await fs.writeFile(`./release/Index.html`,content)
    let ctx = await esbuild.build({
      entryPoints: [`./render/Index.tsx`],
      bundle: true,
      outdir: 'release',
      plugins: [sassPlugin()],
      platform:"node",
      external:["electron"],
      minify: true,
      sourcemap:false
    })
    console.log("build ok")
    }
release();