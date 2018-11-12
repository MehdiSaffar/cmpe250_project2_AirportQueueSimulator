//
// Created by mehdisaffar on 11/12/18.
//

#ifndef PROJECT_PASSENGER_HPP
#define PROJECT_PASSENGER_HPP

struct Passenger {
    int pid;
    bool isVip;
    bool hasLuggage;

    int arrivalTime;
    int luggageTime;
    int securityTime;
    int flightTime;
    int queueEnterTime;
};
#endif //PROJECT_PASSENGER_HPP
