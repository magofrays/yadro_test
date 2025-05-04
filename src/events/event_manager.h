#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H
#include <string>
#include <memory>
#include "event.h"
#include "arrival_event.h"
#include "wait_event.h"
#include "sitdown_event.h"
#include "quit_event.h"
#include "club_system.h"
#include "errors.h"
#include <iostream>

class eventManager
{
    clubSystem *system;
    std::vector<Event *> events;
    bool initialized = false;

public:
    eventManager() = default;
    void create_event(const std::string &event_string);
    void execute();
    friend std::istream &operator>>(std::istream &is, eventManager &manager);
    friend std::ostream &operator<<(std::ostream &os, const eventManager &manager);
    ~eventManager();
};

#endif