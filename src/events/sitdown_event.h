#ifndef SITDOWN_EVENT_H
#define SITDOWN_EVENT_H
#include "event.h"
#include "clock.h"
class sitdownEvent : public Event
{
    Clock time;
    int id;
    std::string client_name;
    int table_id;

public:
    sitdownEvent(Clock &time, int id, std::string &client_name, int table_id) : time(time), id(id), client_name(client_name), table_id(table_id) {}
    sitdownEvent(Clock &time, int id, std::string &body);
    void execute(clubSystem *system);
    std::string to_string();
};

#endif