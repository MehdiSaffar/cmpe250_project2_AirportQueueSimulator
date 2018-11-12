//
// Created by mehdisaffar on 11/12/18.
//

#ifndef PROJECT_CASEREPORT_H
#define PROJECT_CASEREPORT_H

#include <string>

struct CaseReport
{

    CaseReport(double averageWaitingTime, int missedFlightCount);

    std::string toString() const;

    const double averageWaitingTime;
    const int missedFlightCount;
};

#endif //PROJECT_CASEREPORT_H
