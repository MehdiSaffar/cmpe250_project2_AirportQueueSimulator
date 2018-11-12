//
// Created by mehdisaffar on 11/10/18.
//

#ifndef PROJECT_HEADER_HPP
#define PROJECT_HEADER_HPP

#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "Passenger.hpp"
#include "FileInfo.hpp"
#include "SimulationReport.hpp"

enum CaseType
{
    NoSecurityCheckForVIP,
    OnlineTicketing,
    FirstToFlyFirstToServe,
};

enum EventType
{
    EnteringAirport = 0,
    LeavingLuggage = 1,
    LeavingSecurity = 2,
};

struct Event
{
    EventType type;
    int passengerId;
    int arrivalTime;
    int flightTime;
    int time;
};

std::vector<std::string> splitString(std::string const &str);
Airport getFirstLine(const std::string &line);
Passenger getPassengerLine(const std::string &line);
std::vector<std::string> readAllLines(const std::string &filePath);
FileInfo parseFileContent(const std::vector<std::string> &lines);
void writeAllLines(const std::string &filePath, const std::vector<std::string> &lines);
std::vector<std::string> simulationReportToLines(const SimulationReport &simulationReport);

#endif //PROJECT_HEADER_HPP
