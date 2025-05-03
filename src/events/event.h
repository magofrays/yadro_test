#ifndef EVENT_H
#define EVENT_H
#include "club_system.h"

class clubSystem;
class Event
{
public:
    virtual void execute(clubSystem *system) = 0;
};

#endif // !EVENT_H