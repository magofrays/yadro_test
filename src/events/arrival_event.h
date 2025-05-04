#ifndef ARRIVAL_EVENT_H
#define ARRIVAL_EVENT_H
#include "event.h"
#include "clock.h"

class arrivalEvent : public Event
{
    Clock time;
    int id = 1;
    std::string client_name;

public:
    arrivalEvent(Clock &time, std::string body);
    void execute(clubSystem *system);
    std::string to_string();
};

#endif