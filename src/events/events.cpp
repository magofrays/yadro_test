#include "event.h"
#include "club_system.h"
#include "arrival_event.h"
#include "quit_event.h"
#include "sitdown_event.h"
#include "wait_event.h"
#include "error_event.h"

// ARRIVAL EVENT
arrivalEvent::arrivalEvent(Clock &time, std::string body) : time(time)
{
    if (body.find(' ') != std::string::npos)
    {
        throw eventParseError(body);
    }
    client_name = body;
}

void arrivalEvent::execute(clubSystem *system)
{
    system->add_event_to_history(this->to_string());
    if (!system->posible_to_arrive(time))
        return system->create_error(time, "NotOpenYet");
    if (system->client_exists(client_name))
        return system->create_error(time, "YouShallNotPass");
    system->add_client(time, client_name);
}

std::string arrivalEvent::to_string()
{
    return time.to_string() + " " + std::to_string(id) + " " + client_name;
}

// QUIT EVENT
quitEvent::quitEvent(Clock &time, int id, std::string &body) : time(time), id(id)
{
    if (body.find(' ') != std::string::npos)
    {
        throw eventParseError(body);
    }
    client_name = body;
}

void quitEvent::execute(clubSystem *system)
{
    system->add_event_to_history(this->to_string());
    if (!system->client_exists(client_name))
        return system->create_error(time, "ClientUnknown");
    if (system->client_at_table(client_name))
        system->free_table(client_name, time);
    system->remove_client(client_name, time);
}

std::string quitEvent::to_string()
{
    return time.to_string() + " " + std::to_string(id) + " " + client_name;
}

// SITDOWN EVENT
sitdownEvent::sitdownEvent(Clock &time, int id, std::string &body) : time(time), id(id)
{
    int sep = body.find(' ');
    if (sep == std::string::npos)
    {
        throw eventParseError(body);
    }
    client_name = body.substr(0, sep);
    std::string table_num = body.substr(sep + 1);
    if (table_num.find(' ') != std::string::npos)
    {
        throw eventParseError(table_num);
    }
    for (auto &element : table_num)
    {
        if (!std::isdigit(element))
        {
            throw eventParseError(table_num);
        }
    }
    table_id = std::stoi(table_num);
}
void sitdownEvent::execute(clubSystem *system)
{
    system->add_event_to_history(this->to_string());
    if (!system->client_exists(client_name))
        return system->create_error(time, "ClientUnknown");
    else if (!system->is_free(table_id - 1))
        return system->create_error(time, "PlaceIsBusy");
    system->sitdown_client(time, client_name, table_id - 1);
}

std::string sitdownEvent::to_string()
{
    return time.to_string() + " " + std::to_string(id) + " " + client_name + " " + std::to_string(table_id);
}

// WAIT EVENT

waitEvent::waitEvent(Clock &time, std::string body) : time(time)
{
    if (body.find(' ') != std::string::npos)
    {
        throw eventParseError(body);
    }
    client_name = body;
}

void waitEvent::execute(clubSystem *system)
{
    system->add_event_to_history(this->to_string());
    if (system->free_table_exists())
        return system->create_error(time, "ICanWaitNoLonger!");
    if (!system->client_exists(client_name)) // почему-то в условии задания не прописано
        return system->create_error(time, "ClientUnknown");
    if (system->tables_amount() < system->wait_queue_size())
        return system->create_removal(time, client_name);

    system->wait(time, client_name);
}

std::string waitEvent::to_string()
{
    return time.to_string() + " " + std::to_string(id) + " " + client_name;
}

// ERROR EVENT
errorEvent::errorEvent(Clock &time, std::string body) : time(time)
{
    if (body.find(' ') != std::string::npos)
    {
        throw eventParseError(body);
    }
    info = body;
}
void errorEvent::execute(clubSystem *system)
{
    system->add_event_to_history(this->to_string());
}

std::string errorEvent::to_string()
{
    return time.to_string() + " " + std::to_string(id) + " " + info;
}