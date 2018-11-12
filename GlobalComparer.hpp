//
// Created by mehdisaffar on 11/12/18.
//

#ifndef PROJECT_GLOBALCOMPARER_HPP
#define PROJECT_GLOBALCOMPARER_HPP

#include "Common.hpp"
struct GlobalComparer {

    const std::set<CaseType> &caseTypes;

    bool has(CaseType type);

    explicit GlobalComparer(const std::set<CaseType> &caseTypes);

    bool operator()(Event &first, Event &second);
};


#endif //PROJECT_GLOBALCOMPARER_HPP
