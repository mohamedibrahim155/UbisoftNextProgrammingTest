#pragma once
#include <functional>
#include <unordered_map>
#include<string>

class CEvent
{

public:
	template <typename... Args>
	using EVENT = std::function<void(Args...)>;

    template <typename... Args>
    void Subscribe(std::string eventName, EVENT<Args...> callback)
    {
        m_listOfEvents[eventName] = [callback](void* args) {
            InvokeCallback<Args...>(callback, args);
            };
    }
    void UnSubscribe(std::string eventName)
    {
        m_listOfEvents.erase(eventName);
    }
    void UnSubscribeAllEvents()
    {
        m_listOfEvents.clear();
    }

    template <typename... Args>
    void Invoke(std::string eventName, Args... args)
    {
        auto it = m_listOfEvents.find(eventName);
        if (it != m_listOfEvents.end())
        {
            it->second((void*)&args);
        }
    }

private:

    std::unordered_map<std::string, std::function<void(void*)>> m_listOfEvents;

    // Helper to unpack the arguments and call the callback
    template <typename... Args>
    static void InvokeCallback(std::function<void(Args...)>& callback, void* args)
    {
        
        callback(*reinterpret_cast<std::tuple<Args...>*>(args));
    }

};

