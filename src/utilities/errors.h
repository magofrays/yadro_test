#ifndef ERRORS_H
#define ERRORS_H
#include <exception>
#include <string>

class clockParseError : public std::exception
{
    std::string msg;
    std::string wrong_element;

public:
    clockParseError(const std::string &wrong_element) : wrong_element(wrong_element)
    {
        msg = "Error during parsing element: '" + wrong_element + "'!";
    }

    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

class eventCreatorParseError : public std::exception
{
    std::string msg;
    std::string wrong_element;

public:
    eventCreatorParseError(const std::string &wrong_element) : wrong_element(wrong_element)
    {
        msg = "Error during parsing element: '" + wrong_element + "'!";
    }
    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

class eventParseError : public std::exception
{
    std::string msg;
    std::string wrong_element;

public:
    eventParseError(const std::string &wrong_element) : wrong_element(wrong_element)
    {
        msg = "Error during parsing element: '" + wrong_element + "'!";
    }
    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

#endif