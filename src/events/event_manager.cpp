#include "event_manager.h"

void eventManager::create_event(const std::string &event_string)
{
    int first_separator = event_string.find(' ');
    if (first_separator == std::string::npos)
    {
        throw eventManagerParseError(event_string);
    }
    std::string time_str = event_string.substr(0, first_separator);
    std::string id_body = event_string.substr(first_separator + 1);
    int second_separator = id_body.find(' ');
    if (second_separator == std::string::npos)
    {
        throw eventManagerParseError(event_string);
    }
    std::string id_str = id_body.substr(0, second_separator);
    std::string body = id_body.substr(second_separator + 1);
    Clock time;
    try
    {
        time = Clock(time_str);
    }
    catch (clockParseError &e)
    {
        std::cerr << e.what() << "\n";
        throw eventManagerParseError(event_string);
    }
    for (auto &element : id_str)
    {
        if (!isdigit(element))
        {
            throw eventManagerParseError(event_string);
        }
    }
    int id = std::stoi(id_str);
    try
    {
        Event *event;

        switch (id)
        {
        case 1:
            event = new arrivalEvent(time, body);
            break;
        case 2:
            event = new sitdownEvent(time, id, body);
            break;
        case 3:
            event = new waitEvent(time, body);
            break;
        case 4:
            event = new quitEvent(time, id, body);
            break;
        default:
            throw eventManagerParseError(event_string);
        }

        if (event)
        {
            events.push_back(event);
        }
    }
    catch (eventParseError &e)
    {
        std::cerr << e.what() << "\n";
        throw eventManagerParseError(event_string);
    }
}

void eventManager::execute()
{
    if (!initialized)
        return;
    for (auto *event : events)
    {
        event->execute(system);
    }
    system->finish();
}

std::istream &operator>>(std::istream &is, eventManager &manager)
{
    manager.initialized = true;
    int tables_amount;
    std::string time_start;
    std::string time_end;
    int hour_cost;
    std::string input;
    try
    {
        std::getline(is, input);
        tables_amount = std::stoi(input);
    }
    catch (...)
    {
        throw eventManagerParseError(input);
    }
    std::getline(is, time_start, ' ');
    std::getline(is, time_end);
    Clock start;
    Clock end;
    start = Clock(time_start);
    end = Clock(time_end);
    try
    {
        start = Clock(time_start);
        end = Clock(time_end);
    }
    catch (clockParseError &e)
    {
        std::cerr << e.what();
        throw eventManagerParseError(start.to_string() + start.to_string());
    }
    try
    {
        std::getline(is, input);
        hour_cost = std::stoi(input);
    }
    catch (...)
    {
        throw eventManagerParseError(input);
    }

    manager.system = new clubSystem(Clock(time_start), Clock(time_end), hour_cost, tables_amount);
    std::string event_line;
    while (std::getline(is, event_line))
    {
        manager.create_event(event_line);
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const eventManager &manager)
{
    for (auto &element : manager.system->get_history())
    {
        os << element << "\n";
    }
    return os;
}
eventManager::~eventManager()
{
    delete system;
    for (auto *event : events)
    {
        delete event;
    }
}