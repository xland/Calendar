let esbuild = require("esbuild");
let fs = require("fs-extra");
const template = require("./template");

let preparePackageJson = async () => {
  let json = require("../package.json");
  delete json.scripts;
  delete json.license;
  let electronConfig = json.devDependencies.electron.replace("^", "");
  delete json.devDependencies;
  json.devDependencies = { electron: electronConfig };
  fs.writeFileSync("./prod/package.json", JSON.stringify(json));
  //防止electron-builder再安装一次依赖
  fs.mkdirSync("./prod/node_modules");
};

let buildMain = async () => {
  await fs.copy("./build/", "./prod/build/");
  await esbuild.build({
    entryPoints: ["./main/entry.ts"],
    bundle: true,
    outfile: "./prod/main.js",
    platform: "node",
    external: ["electron"],
    minify: true,
    sourcemap: false,
  });
};

let buildRender = async () => {
  let { sassPlugin } = require("esbuild-sass-plugin");
  await fs.copy("./dev/res/", "./prod/res");
  let arr = ["Index", "IndexJob", "IndexAlert"];
  for (let item of arr) {
    let content = template.get(item, false);
    await fs.writeFile(`./prod/${item}.html`, content);
  }
  await esbuild.build({
    entryPoints: arr.map((v) => `./render/${v}.tsx`),
    bundle: true,
    outdir: "prod",
    plugins: [sassPlugin()],
    platform: "node",
    external: ["electron"],
    minify: true,
    sourcemap: false,
  });
};

let buildInstaller = () => {
  let options = {
    config: {
      directories: { output: "./dist", app: "./prod" },
      files: ["**"],
      extends: null,
      productName: "Calendar",
      appId: "com.calendar.xland",
      asar: true,
      // extraResources,
      win: {
        icon: "./script/logo.ico",
        target: [{ target: "nsis", arch: ["x64"] }],
      },
      // mac: macConfig,
      nsis: {
        oneClick: true,
        perMachine: true,
        allowToChangeInstallationDirectory: false,
        // include: path.join(process.cwd(), 'script/common/installer32.nsh'),
        createDesktopShortcut: true,
        createStartMenuShortcut: true,
        shortcutName: "Calendar",
        installerIcon: "./script/logo.ico",
        uninstallerIcon: "./script/logo.ico",
        installerHeader: "./script/logo.ico",
        installerHeaderIcon: "./script/logo.ico",
        // installerSidebar: '../resource/unrelease/sidebar.bmp',
      },
      publish: [{ provider: "generic", url: "" }],
    },
    // project: process.cwd(),
  };
  let builder = require("electron-builder");
  return builder.build(options);
};

let start = async () => {
  await fs.remove("./prod");
  fs.mkdirSync("./prod");
  await buildMain();
  await buildRender();
  await preparePackageJson();
  await buildInstaller();
};
start();
