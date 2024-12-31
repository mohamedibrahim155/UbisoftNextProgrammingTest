#pragma once
#include <functional>
#include <unordered_map>
#include<string>

template <typename... Args>
class CEvent
{

public:
    using EVENT = std::function<void(Args...)>;

    void Subscribe(EVENT callback) 
    {
        m_callbacks.push_back(std::move(callback));
    }

    void Invoke(Args... args) 
    {
        for (auto& callback : m_callbacks) 
        {
            if (callback)
            {
                callback(args...);
            }
        }
    }

    void clear()
    {
        m_callbacks.clear();
    }

private:
    std::vector<EVENT> m_callbacks;
};

