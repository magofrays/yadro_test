#ifndef ERROR_EVENT_H
#define ERROR_EVENT_H
#include "event.h"
#include "club_system.h"
class errorEvent : public Event
{
    Clock time;
    int id = 13;
    std::string info;

public:
    errorEvent(Clock &time, std::string body);
    void execute(clubSystem *system);
    std::string to_string();
};

#endif