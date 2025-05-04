#ifndef QUIT_EVENT_H
#define QUIT_EVENT_H
#include "event.h"
#include "error_event.h"
#include "clock.h"

class quitEvent : public Event
{
    Clock time;
    int id;
    std::string client_name;

public:
    quitEvent(Clock &time, int id, std::string body);
    void execute(clubSystem *system);
    std::string to_string();
};

#endif