#include "stdafx.h"
#include "Event.h"

void CEvent::Subscribe(std::string eventName, EVENT callback)
{
    m_listOfEvents[eventName] = callback;

}


void CEvent::UnSubscribe(std::string eventName)
{
    m_listOfEvents.erase(eventName);
}

void CEvent::Invoke()
{
    for (std::pair<std::string, EVENT> event : m_listOfEvents)
    {
        if (event.second) 
        {
            event.second();
        }
    }
}
