#include "event_manager.h"
#include <fstream>

int main(int argc, char const *argv[])
{
    std::string dir = "../yadro_test/example.txt";
    std::ifstream file(dir);
    if (!file.is_open())
    {
        throw std::invalid_argument("Error: there is no such file in path: '" + dir + "'!");
    }
    eventManager manager;
    file >> manager;
    manager.execute();
    std::cout << manager;
    return 0;
}
