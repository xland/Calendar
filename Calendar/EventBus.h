#pragma once
#include <map>
#include <string>
#include <functional>

class EventBus
{
public:
	static void emit(const std::string& eventName);
	static void on(const std::string& eventName,const std::function<void()>& fn);
private:
};

