#pragma once
#include <functional>
#include <unordered_map>

class CEvent
{

public:
	using EVENT = std::function<void()>;
	void Subscribe(std::string eventName, EVENT callback);
	void UnSubscribe(std::string eventName);
	void UnSubscribeAllEvents();

	void Invoke();

private:

	std::unordered_map<std::string,EVENT> m_listOfEvents;

};

