//
// Created by felix on 21/04/23.
//

#include "Logger.hpp"
#include <iostream>
#include <ctime>
#include <experimental/source_location>
#include <filesystem>

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define LOGLEVEL 3


void Logger::info(const std::string msg, const std::experimental::source_location location) {
    std::string time = Logger::getTime();
    std::string loc = Logger::getLocation(location);
    std::cout << time << " " << loc << BOLDGREEN << " [INFO] : " << msg << RESET << std::endl;

}

void Logger::error(const std::string msg, const std::experimental::source_location location) {
    std::string time = Logger::getTime();
    std::string loc = Logger::getLocation(location);
    std::cout << time << " " << loc << BOLDRED << " [ERROR] : " << msg << RESET << std::endl;

}

void Logger::debug(const std::string msg, const std::experimental::source_location location) {
    if (LOGLEVEL > 1) {
        std::string time = Logger::getTime();
        std::string loc = Logger::getLocation(location);
        std::cout << time << " " << loc << BOLDYELLOW << " [DEBUG] : " << msg << RESET << std::endl;
    }
}

void Logger::verbose(const std::string msg, const std::experimental::source_location location) {
    if (LOGLEVEL > 2) {
        std::string time = Logger::getTime();
        std::string loc = Logger::getLocation(location);
        std::cout << time << " " << loc << BOLDMAGENTA << " [VERBOSE] : " << msg << RESET << std::endl;
    }
}


std::string Logger::getTime() {
    // Get the current time
    std::time_t now = std::time(nullptr);
    // Format the date as 'dd-mm-yyyy HH:MM:SS' (total of 19 chars)
    char formatedDate[21];
    strftime(formatedDate, 21, "%d-%m-%Y %H:%M:%S", std::localtime(&now));
    std::stringstream ss;
    ss << CYAN << "[" << formatedDate << "]" << RESET;
    return ss.str();
}

std::string Logger::getLocation(const std::experimental::source_location location) {
    std::stringstream ss;
    ss << BOLDBLUE << "[" << std::filesystem::path(location.file_name()).filename() << " " << location.function_name() << ":" << location.line() << "] " << RESET;
    return ss.str();
}