#ifndef ERROR_EVENT_H
#define ERROR_EVENT_H
#include "event.h"
class errorEvent : public Event
{
    Clock time;
    int id = 13;
    std::string info;

public:
    errorEvent(Clock &time, std::string body) : time(time)
    {
        if (body.find(' ') != std::string::npos)
        {
            throw eventParseError(body);
        }
    }
    void execute(clubSystem *system)
    {
        system->add_event_to_history(this);
    }
};

#endif