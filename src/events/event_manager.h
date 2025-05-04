#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <memory>
#include "event.h"
#include "errors.h"
#include "clock.h"
#include <iostream>

class eventManager
{
public:
    std::unique_ptr<Event> create_event(const std::string &event_string)
    {
        int first_separator = event_string.find(' ');
        if (first_separator == std::string::npos)
        {
            throw eventCreatorParseError(event_string);
        }
        std::string time_str = event_string.substr(0, first_separator);
        std::string id_body = event_string.substr(first_separator + 1);
        int second_separator = id_body.find(' ');
        if (second_separator == std::string::npos)
        {
            throw eventCreatorParseError(event_string);
        }
        std::string id_str = event_string.substr(0, second_separator);
        std::string body = event_string.substr(second_separator + 1);
        try
        {
            Clock time(time_str);
        }
        catch (clockParseError &e)
        {
            std::cerr << e.what() << "\n";
            throw eventCreatorParseError(event_string);
        }
        for (auto &element : id_str)
        {
            if (!isdigit(element))
            {
                throw eventCreatorParseError(event_string);
            }
        }
        int id = std::stoi(id_str);
        switch (id)
        {
        case 1:

        case 2:
            break;
        case 3:
            break;
        case 4:

            break;
        default:
            throw eventCreatorParseError(event_string);
        }
    }
};

#endif