#include "club_system.h"

clubSystem::clubSystem(Clock start, Clock end, int hour_cost, int tables_amount) : start(start), end(end), hour_cost(hour_cost), tables(std::vector<clubTable>(tables_amount))
{
    history.push_back(start.to_string());
}

void clubSystem::free_table(std::string &name, Clock &time)
{
    int i = 0;
    for (; i != tables.size(); i++)
    {
        if (!tables[i].empty && name == tables[i].curr_client)
        {
            Clock worked = time - tables[i].client_time;
            tables[i].worked = tables[i].worked + worked;
            int hours = worked.hours + (worked.minutes > 0 ? 1 : 0);
            tables[i].earned_money += hours * hour_cost;
            tables[i].empty = true;
            break;
        }
    }
    if (!waiting_clients.empty())
    {
        std::string w_name = waiting_clients.front();
        create_sitdown(time, w_name, i + 1);
        waiting_clients.pop();
    }
}

bool clubSystem::free_table_exists()
{
    for (auto &table : tables)
    {
        if (table.empty)
        {
            return true;
        }
    }
    return false;
}

void clubSystem::wait(Clock &time, std::string &client_name)
{
    waiting_clients.push(client_name);
}

void clubSystem::add_client(Clock &time, std::string &name)
{
    current_clients.push_back(name);
}

void clubSystem::sitdown_client(Clock &time, std::string &name, int table_id)
{
    tables[table_id].empty = false;
    tables[table_id].client_time = time;
    tables[table_id].curr_client = name;
}

void clubSystem::remove_client(std::string &name, Clock &time)
{
    current_clients.erase(std::find(current_clients.begin(), current_clients.end(), name));
}

void clubSystem::create_sitdown(Clock &time, std::string &client_name, int table_id)
{
    sitdownEvent event(time, 12, client_name, table_id);
    event.execute(this);
}

void clubSystem::create_removal(Clock &time, std::string &client_name)
{
    quitEvent event(time, 11, client_name);
    event.execute(this);
}

void clubSystem::create_error(Clock &time, std::string info)
{
    errorEvent error(time, info);
    error.execute(this);
}

bool clubSystem::client_at_table(std::string &name)
{
    for (auto &table : tables)
    {
        if (!table.empty && table.curr_client == name)
            return true;
    }
    return false;
}

bool clubSystem::client_exists(std::string &name)
{
    return current_clients.size() > 0 && std::find(current_clients.begin(), current_clients.end(), name) != current_clients.end();
}

bool clubSystem::posible_to_arrive(Clock time)
{
    return (time > start && time < end);
}

void clubSystem::add_event_to_history(std::string event)
{
    history.push_back(event);
}

bool clubSystem::is_free(int table_id)
{
    if (table_id >= tables.size() || table_id < 0)
        throw std::logic_error("out of range");

    return tables[table_id].empty;
}

int clubSystem::tables_amount()
{
    return tables.size();
}

int clubSystem::wait_queue_size()
{
    return waiting_clients.size();
}

void clubSystem::table_result()
{
    for (int id = 0; id != tables.size(); id++)
    {
        std::string result = std::to_string(id + 1) + " " + std::to_string(tables[id].earned_money) + " " + tables[id].worked.to_string();
        history.push_back(result);
    }
}
void clubSystem::finish()
{
    std::sort(current_clients.begin(), current_clients.end());
    for (auto &name : current_clients)
    {
        create_removal(end, name);
    }

    history.push_back(end.to_string());
    table_result();
}