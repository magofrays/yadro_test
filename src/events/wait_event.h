#ifndef WAIT_EVENT_H
#define WAIT_EVENT_H
#include "event.h"
class waitEvent : public Event
{
    Clock time;
    int id = 3;
    std::string client_name;

public:
    waitEvent(Clock &time, std::string body);
    void execute(clubSystem *system);
    std::string to_string();
};

#endif