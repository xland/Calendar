module.exports = {
  get(item, isDev) {
    let devScriptStr = isDev ? `<script>new EventSource('/esbuild').addEventListener('change', () => location.reload())</script>` : ``;
    let str = `<html><head><meta http-equiv="Content-Type" content="text/html;charset=UTF-8"><link rel="stylesheet" href="./res/iconfont.css">
<link rel="stylesheet" href="./${item}.css"></head><body class="blue"><script src="./${item}.js"></script>${devScriptStr}</body></html>`;
    return str;
  },
};
