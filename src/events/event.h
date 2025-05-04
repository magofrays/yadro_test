#ifndef EVENT_H
#define EVENT_H
#include <iostream>

class clubSystem;

class Event
{
public:
    virtual void execute(clubSystem *system) = 0;
    virtual std::string to_string() = 0;
    virtual ~Event() {}
};

#endif // !EVENT_H