#ifndef CLUB_SYSTEM_H
#define CLUB_SYSTEM_H
#include "errors.h"
#include "clock.h"
#include <queue>
#include "event.h"
#include <memory>
#include <algorithm>
#include "error_event.h"
#include "sitdown_event.h"
#include "quit_event.h"

class arrivalEvent;
struct clubTable
{
    Clock worked;
    int earned_money;
    bool empty;
    std::string curr_client;
    Clock client_time;
    clubTable() : worked(), earned_money(0), empty(true), curr_client("") {}
};

class clubSystem
{
    Clock start;
    Clock end;
    int hour_cost;
    std::vector<clubTable> tables;
    std::queue<std::string> waiting_clients;
    std::vector<std::string> current_clients;
    std::vector<std::string> history;

public:
    clubSystem(Clock start, Clock end, int hour_cost, int table_num);
    void free_table(std::string &name, Clock &time);
    bool free_table_exists();
    void wait(Clock &time, std::string &client_name);
    void add_client(Clock &time, std::string &name);
    void sitdown_client(Clock &time, std::string &name, int table_id);
    void remove_client(std::string &name, Clock &time);
    void create_sitdown(Clock &time, std::string &client_name, int table_id);
    void create_removal(Clock &time, std::string &client_name);
    void create_error(Clock &time, std::string info);
    bool client_at_table(std::string &name);
    bool client_exists(std::string &name);
    bool posible_to_arrive(Clock time);
    void add_event_to_history(std::string event);
    const std::vector<std::string> &get_history() const { return history; }
    void table_result();
    bool is_free(int table_id);
    int tables_amount();
    int wait_queue_size();
    void finish();

    friend class eventManager;
};
#endif
