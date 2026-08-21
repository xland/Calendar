#pragma once
#include <include/Ling.h>

class App
{
	public:
		~App();
		static void init();
		// 消息循环退出后、Ling::dispose 之前调用：单例和窗口对象里存着 WinRT / D2D 对象
		//（配置和语言是 JsonObject，贴图窗口攥着位图和画刷），等到进程退出后的静态析构时
		// CoUninitialize 早跑完了，析构里那句 Release 打到的是已经拆掉的对象 ——
		// 表现为读取访问权限冲突
		static void dispose();
		static App* get();
	private:
		App();
};

