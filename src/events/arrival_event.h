#ifndef ARRIVAL_EVENT_H
#define ARRIVAL_EVENT_H
#include "event.h"
#include "error_event.h"

class arrivalEvent : public Event
{
    Clock time;
    int id;
    std::string name;

public:
    arrivalEvent(Clock &time, std::string body)
    {
        if (body.find(' ') != std::string::npos)
        {
            throw eventParseError(body);
        }
    }
    void execute(clubSystem *system)
    {
        system->add_event_to_history(this);
        if (system->posible_to_arrive(time))
        {
            errorEvent error(time, "NotOpenYet");
            error.execute(system);
            return;
        }
        if (system->client_exists(name))
        {
            errorEvent error(time, "YouShallNotPass");
            error.execute(system);
            return;
        }
    }
};

#endif // !ARRIVAL_EVENT_H