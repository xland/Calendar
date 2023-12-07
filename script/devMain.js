let esbuild = require("esbuild")
let {sassPlugin} = require("esbuild-sass-plugin")
let fs = require("fs-extra")
let start = async ()=>{
    esbuild.buildSync({
        entryPoints: ['./main/entry.ts'],
        bundle: true,
        outfile:"./prod/main.js",
        platform:"node",
        external:["electron"],
        sourcemap:true
      })
}
start();