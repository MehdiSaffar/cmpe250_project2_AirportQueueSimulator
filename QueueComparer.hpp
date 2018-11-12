//
// Created by mehdisaffar on 11/12/18.
//

#ifndef PROJECT_QUEUECOMPARER_HPP
#define PROJECT_QUEUECOMPARER_HPP

#include "Passenger.hpp"
#include "Common.hpp"

struct QueueComparer {
    const std::set<CaseType> &caseTypes;

    explicit QueueComparer(const std::set<CaseType> &caseTypes);

    bool has(CaseType type);

    bool operator()(Passenger &first, Passenger &second);
};





#endif //PROJECT_QUEUECOMPARER_HPP
