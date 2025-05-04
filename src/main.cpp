#include "event_manager.h"

int main(int argc, char const *argv[])
{
    eventManager manager;
    std::cin >> manager;
    manager.execute();
    std::cout << "\n"
              << manager;
    return 0;
}
