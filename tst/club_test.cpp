#include "event_manager.h"
#include <fstream>
#include <sstream>
#include <gtest/gtest.h>

std::string file_to_string(std::ifstream &file)
{
    return std::string(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
}
TEST(CLUB_SYSTEM, DEFAULT_TEST)
{
    std::ifstream test("../../yadro_test/tst/tests/1test.txt");
    std::ifstream answer("../../yadro_test/tst/tests/1answer.txt");
    if (!test.is_open() || !answer.is_open())
        throw std::invalid_argument("wrong test dir");
    eventManager manager;
    test >> manager;
    manager.execute();
    std::stringstream result;
    result << manager;
    ASSERT_EQ(result.str(), file_to_string(answer));
    test.close();
    answer.close();
}

TEST(CLUB_SYSTEM, NOT_EMPTY_QUEUE_END_OF_DAY)
{
    std::ifstream test("../../yadro_test/tst/tests/2test.txt");
    std::ifstream answer("../../yadro_test/tst/tests/2answer.txt");
    if (!test.is_open() || !answer.is_open())
        throw std::invalid_argument("wrong test dir");
    eventManager manager;
    test >> manager;
    manager.execute();
    std::stringstream result;
    result << manager;
    ASSERT_EQ(result.str(), file_to_string(answer));
    test.close();
    answer.close();
}

TEST(CLUB_SYSTEM, A_LOT_OF_ERRORS)
{
    std::ifstream test("../../yadro_test/tst/tests/3test.txt");
    std::ifstream answer("../../yadro_test/tst/tests/3answer.txt");
    if (!test.is_open() || !answer.is_open())
        throw std::invalid_argument("wrong test dir");
    eventManager manager;
    test >> manager;
    manager.execute();
    std::stringstream result;
    result << manager;
    ASSERT_EQ(result.str(), file_to_string(answer));
    test.close();
    answer.close();
}