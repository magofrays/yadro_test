#ifndef CLUB_SYSTEM_H
#define CLUB_SYSTEM_H
#include "errors.h"
#include "clock.h"
#include <queue>
#include "event.h"
#include <memory>

class arrivalEvent;
struct clubTable
{
    Clock worked;
    int earned_money;
    bool empty;
    std::string curr_client;
    Clock client_time;
};

class clubSystem
{
    Clock start;
    Clock end;
    std::vector<clubTable> tables;
    // std::queue<waitEvent> waiting;
    std::vector<arrivalEvent> arrived;
    std::vector<Event *> history;

public:
    void free_table(std::string &user, Clock time)
    {
        for (auto &table : tables)
        {
            if (!table.empty && user == table.curr_client)
            {
                Clock worked = time - table.client_time;
                table.worked = table.worked + worked;
                table.empty = true;
            }
        }
    }
    bool client_exists(std::string &name)
    {
        for (auto &table : tables)
        {
            if (!table.empty && table.curr_client == name)
            {
                return true;
            }
        }
        return false;
    }

    bool posible_to_arrive(Clock time)
    {
        return (time > start && time < end);
    }

    void add_event_to_history(Event *event)
    {
        history.push_back(event);
    }
};

#endif // !CLUB_SYSTEM_H
