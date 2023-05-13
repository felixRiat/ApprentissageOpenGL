//
// Created by felix on 21/04/23.
//

#ifndef TEST_LOGGER_HPP
#define TEST_LOGGER_HPP


#include <string>
#include <experimental/source_location>

class Logger {
public:
    void info(std::string msg, std::experimental::source_location location = std::experimental::source_location::current());
    void error(std::string msg, std::experimental::source_location location = std::experimental::source_location::current());
    void debug(std::string msg, std::experimental::source_location location = std::experimental::source_location::current());
    void verbose(std::string msg, std::experimental::source_location location = std::experimental::source_location::current());

private:
    std::string getTime();
    std::string getLocation(std::experimental::source_location location);
};


#endif //TEST_LOGGER_HPP
