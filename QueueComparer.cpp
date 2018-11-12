//
// Created by mehdisaffar on 11/12/18.
//

#include "QueueComparer.hpp"

QueueComparer::QueueComparer(const std::set<CaseType > &caseTypes) : caseTypes(caseTypes) {
}

bool QueueComparer::has(CaseType type) {
    return this->caseTypes.find(type) != this->caseTypes.end();
}

bool QueueComparer::operator()(Passenger &first, Passenger &second) {
    if (has(FirstToFlyFirstToServe)) { // In case first to fly
        if (first.flightTime == second.flightTime) {
            return !(first.arrivalTime <= second.arrivalTime);
        }
        return !(first.flightTime <= second.flightTime);
    } else {
        if (first.queueEnterTime == second.queueEnterTime) {
            return !(first.arrivalTime <= second.arrivalTime);
        }
        return !(first.queueEnterTime <= second.queueEnterTime);
    }
}
