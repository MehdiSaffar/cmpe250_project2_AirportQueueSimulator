//
// Created by mehdisaffar on 11/12/18.
//

#ifndef PROJECT_FILEINFO_H
#define PROJECT_FILEINFO_H


#include <vector>
#include "Airport.hpp"
#include "Passenger.hpp"

struct FileInfo {
    Airport airport;
    std::vector<Passenger> passengers;
};


#endif //PROJECT_FILEINFO_H
