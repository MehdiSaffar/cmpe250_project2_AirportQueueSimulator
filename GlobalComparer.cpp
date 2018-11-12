//
// Created by mehdisaffar on 11/12/18.
//

#include "GlobalComparer.hpp"

GlobalComparer::GlobalComparer(const std::set<CaseType > &caseTypes) : caseTypes(caseTypes) {
}

bool GlobalComparer::operator()(Event &first, Event &second) {
    if (first.time == second.time) {
        if (first.type == second.type) {
            if (has(FirstToFlyFirstToServe)) { // In case FirstToFlyFirstToServe-to-Fly FirstToFlyFirstToServe-to-Serve
                if (first.flightTime == second.flightTime) {
                    return !(first.arrivalTime <= second.arrivalTime);
                }
                return !(first.flightTime <= second.flightTime);
            } else {
                return !(first.arrivalTime <= second.arrivalTime);
            }
        }
        return !(first.type >= second.type);
    }

    return !(first.time <= second.time);
}

bool GlobalComparer::has(CaseType type) {
    return this->caseTypes.find(type) != this->caseTypes.end();
}
