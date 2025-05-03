#ifndef QUIT_EVENT_H
#define QUIT_EVENT_H
#include "event.h"
#include "error_event.h"
#include "clock.h"

class quitEvent : public Event
{
    Clock time;
    int id;
    std::string name;

public:
    quitEvent(Clock &time, int id, std::string body)
    {
        if (body.find(' ') != std::string::npos)
        {
            throw eventParseError(body);
        }
    }
    void execute(clubSystem *system)
    {
        system->add_event_to_history(this);
        if (!system->client_exists(name))
        {
            errorEvent error(time, "ClientUnknown");
            error.execute(system);
            return;
        }
        system->free_table(name, time);
        // system->ждуны
    }
};

#endif