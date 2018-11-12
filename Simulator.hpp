//
// Created by mehdisaffar on 11/12/18.
//

#ifndef PROJECT_SIMULATOR_H
#define PROJECT_SIMULATOR_H

#include <set>
#include <queue>
#include "CaseReport.hpp"
#include "Common.hpp"
#include "FileInfo.hpp"
#include "GlobalComparer.hpp"
#include "QueueComparer.hpp"
#include "SimulationReport.hpp"

class Simulator
{
    const Airport airport;
    std::set<CaseType> features;

  public:
    explicit Simulator(const Airport &airport);

    CaseReport simulateCase(const FileInfo &fileInfo);

    bool canGoToLuggage(int inLuggageCount);

    bool canGoToSecurity(int inSecurityCount);

    bool canSkipLuggage(const Passenger &passenger);

    bool canSkipSecurity(const Passenger &passenger);

    void setFeatures(const std::set<CaseType> &features);

    bool hasFeature(const CaseType &feature) const;

    void calculateWaitAndMissed(int currentTime, int arrivalTime, int flightTime, int &missedCount, double &averageTime);

    SimulationReport simulateAllCases(const FileInfo &info);
};

#endif //PROJECT_SIMULATOR_H
