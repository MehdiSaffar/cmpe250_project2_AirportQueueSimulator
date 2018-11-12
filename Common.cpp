//
// Created by mehdisaffar on 11/12/18.
//
#include "Common.hpp"

std::vector<std::string> splitString(std::string const &str) {
    std::vector<std::string> out;
    // construct a stream from the string
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, ' ')) {
        out.push_back(s);
    }
    return out;
}

Airport getFirstLine(const std::string &line) {
    std::vector<std::string> tokens = splitString(line);
    Airport airportInfo = {};
    airportInfo.luggageCount = std::stoi(tokens[1]);
    airportInfo.securityCount = std::stoi(tokens[2]);

    return airportInfo;
}


Passenger getPassengerLine(const std::string &line) {
    std::vector<std::string> tokens = splitString(line);
    Passenger passengerInfo = {};
    passengerInfo.arrivalTime = stoi(tokens[0]);
    passengerInfo.flightTime = stoi(tokens[1]);
    passengerInfo.luggageTime = stoi(tokens[2]);
    passengerInfo.securityTime = stoi(tokens[3]);
    passengerInfo.isVip = tokens[4] == "V"; // else no
    passengerInfo.hasLuggage = tokens[5] == "L"; // else no
    return passengerInfo;
}

std::vector<std::string> readAllLines(const std::string &filePath) {
    std::ifstream inputFile(filePath);
    std::vector<std::string> lines;
    std::string line;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    return lines;
}


FileInfo parseFileContent(const std::vector<std::string> &lines) {
    FileInfo result = {};
    result.airport = getFirstLine(lines[0]);
    // get passenger info
    for (int i = 1; i < lines.size(); i++) {
        result.passengers.push_back(getPassengerLine(lines[i]));
    }
    return result;
}

void writeAllLines(const std::string& filePath, const std::vector<std::string>& lines) {
    std::ofstream outputFile;
    outputFile.open(filePath);
    for(const auto& line : lines) {
        outputFile << line << std::endl;
    }
    outputFile.close();
}

std::vector<std::string> simulationReportToLines(const SimulationReport& simulationReport) {
    std::vector<std::string> outputLines;
    for (const auto &caseReport : simulationReport.caseReports) {
        std::string line = caseReport.toString();
        outputLines.push_back(line);
    }
    return outputLines;
}
