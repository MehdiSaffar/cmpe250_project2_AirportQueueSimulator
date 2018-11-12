//
// Created by mehdisaffar on 11/12/18.
//

#ifndef PROJECT_SIMULATIONREPORT_H
#define PROJECT_SIMULATIONREPORT_H

#include <vector>
#include "CaseReport.hpp"

struct SimulationReport
{
    const std::vector<CaseReport> caseReports;

    explicit SimulationReport(const std::vector<CaseReport> &caseReports);
};

#endif //PROJECT_SIMULATIONREPORT_H
