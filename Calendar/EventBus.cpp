#include "EventBus.h"

std::map<const std::string, std::function<void()>> eventMap;

void EventBus::on(const std::string& eventName,const std::function<void()>& fn) {
	eventMap[eventName] = fn;
}

void EventBus::emit(const std::string& eventName) {
	if (eventMap[eventName] != nullptr) {
		eventMap[eventName]();
	}
}