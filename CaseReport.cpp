//
// Created by mehdisaffar on 11/12/18.
//

#include <sstream>
#include "CaseReport.hpp"

CaseReport::CaseReport(double averageWaitingTime, int missedFlightCount) : averageWaitingTime(averageWaitingTime), missedFlightCount(missedFlightCount) {}

std::string CaseReport::toString() const
{
    std::stringstream ss;
    ss << this->averageWaitingTime << " " << this->missedFlightCount;
    return ss.str();
}
