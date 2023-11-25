import React from "./React";
import "./SettingDonate.scss";
export default function (props) {
  return (
    <div class="settingBox" id="settingDonate">
      <div>
        <img src="./res/wechat.png" alt="" />
        <div>微信支付</div>
      </div>
      <div>
        <img src="./res/alipay.jpg" alt="" />
        <div>支付宝支付</div>
      </div>
    </div>
  );
}
