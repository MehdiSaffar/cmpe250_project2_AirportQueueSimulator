//
// Created by mehdisaffar on 11/12/18.
//

#include "Simulator.hpp"

bool Simulator::canGoToLuggage(int inLuggageCount)
{
    return inLuggageCount < this->airport.luggageCount;
}

bool Simulator::canSkipLuggage(const Passenger &passenger)
{
    return !passenger.hasLuggage && hasFeature(OnlineTicketing);
}

bool Simulator::canSkipSecurity(const Passenger &passenger)
{
    return passenger.isVip && hasFeature(NoSecurityCheckForVIP);
}

bool Simulator::canGoToSecurity(int inSecurityCount)
{
    return inSecurityCount < this->airport.securityCount;
}

bool Simulator::hasFeature(const CaseType &feature) const
{
    return this->features.find(feature) != this->features.end();
}

void Simulator::calculateWaitAndMissed(int currentTime, int arrivalTime, int flightTime, int &missedCount, double &averageTime)
{
    if (currentTime > flightTime)
    {
        missedCount++;
    }
    averageTime += (double)(currentTime - arrivalTime);
}

CaseReport Simulator::simulateCase(const FileInfo &fileInfo)
{
    int busyLuggageCounterCount = 0;
    int busySecurityCounterCount = 0;
    int missedFlightCount = 0;
    double averageWaitTime = 0.0;

    GlobalComparer comp(this->features);
    QueueComparer queueComparer(this->features);

    std::priority_queue<Event, std::vector<Event>, GlobalComparer> q(comp);
    std::priority_queue<Passenger, std::vector<Passenger>, QueueComparer> securityQueue(queueComparer);
    std::priority_queue<Passenger, std::vector<Passenger>, QueueComparer> luggageQueue(queueComparer);

    std::vector<Passenger> passengers = fileInfo.passengers;

    for (int i = 0; i < passengers.size(); ++i)
    {
        Passenger &passenger = passengers[i];
        passenger.pid = i;
        Event event;
        event.passengerId = i;
        event.time = passenger.arrivalTime;
        event.flightTime = passenger.flightTime;
        event.arrivalTime = passenger.arrivalTime;
        event.type = EnteringAirport;
        q.push(event);
    }

    while (!q.empty())
    {
        Event current = q.top();
        q.pop();

        Passenger passenger = passengers[current.passengerId];
        Event next = current;
        if (current.type == EnteringAirport)
        {
            if (canSkipLuggage(passenger))
            {
                if (canSkipSecurity(passenger))
                {
                    calculateWaitAndMissed(current.time, passenger.arrivalTime, passenger.flightTime, missedFlightCount, averageWaitTime);
                }
                else
                {
                    if (canGoToSecurity(busySecurityCounterCount))
                    {
                        next.time += passenger.securityTime;
                        next.type = LeavingSecurity;
                        busySecurityCounterCount++;
                        q.push(next);
                    }
                    else
                    { // Security counters are full
                        passenger.queueEnterTime = current.time;
                        securityQueue.push(passenger);
                    }
                }
            }
            else
            {
                if (canGoToLuggage(busyLuggageCounterCount))
                {
                    next.time = current.time + passenger.luggageTime;
                    next.type = LeavingLuggage;
                    busyLuggageCounterCount++;
                    q.push(next);
                }
                else
                { // Luggage counters are full
                    passenger.queueEnterTime = current.time;
                    luggageQueue.push(passenger);
                }
            }
        }
        else if (current.type == LeavingLuggage)
        {
            busyLuggageCounterCount--;
            if (!luggageQueue.empty())
            {
                busyLuggageCounterCount++;
                Passenger nextP = luggageQueue.top();
                luggageQueue.pop();
                Event nextPE = current;
                nextPE.passengerId = nextP.pid;
                nextPE.time = current.time + nextP.luggageTime;
                nextPE.arrivalTime = nextP.arrivalTime;
                nextPE.flightTime = nextP.flightTime;
                nextPE.type = LeavingLuggage;
                q.push(nextPE);
            }
            if (canSkipSecurity(passenger))
            {
                calculateWaitAndMissed(current.time, passenger.arrivalTime, passenger.flightTime, missedFlightCount, averageWaitTime);
            }
            else
            {
                if (canGoToSecurity(busySecurityCounterCount))
                {
                    next.time = current.time + passenger.securityTime;
                    next.type = LeavingSecurity;
                    busySecurityCounterCount++;
                    q.push(next);
                }
                else
                { // Security counters are full
                    passenger.queueEnterTime = current.time;
                    securityQueue.push(passenger);
                }
            }
        }
        else if (current.type == LeavingSecurity)
        {
            busySecurityCounterCount--;
            if (!securityQueue.empty())
            {
                busySecurityCounterCount++;
                Passenger nextP = securityQueue.top();
                securityQueue.pop();
                Event nextPE;
                nextPE.passengerId = nextP.pid;
                nextPE.time = current.time + nextP.securityTime;
                nextPE.arrivalTime = nextP.arrivalTime;
                nextPE.flightTime = nextP.flightTime;
                nextPE.type = LeavingSecurity;
                q.push(nextPE);
            }
            calculateWaitAndMissed(current.time, passenger.arrivalTime, passenger.flightTime, missedFlightCount, averageWaitTime);
        }
    }

    averageWaitTime /= (double)passengers.size();

    CaseReport caseReport(averageWaitTime, missedFlightCount);
    return caseReport;
}

void Simulator::setFeatures(const std::set<CaseType> &features)
{
    this->features = features;
}

Simulator::Simulator(const Airport &airport) : airport(airport) {}

std::set<CaseType> getCaseTypes(bool onlineTicketing, bool noSecurityCheck, bool firstFly)
{
    std::set<CaseType> types;
    if (onlineTicketing)
    {
        types.insert(OnlineTicketing);
    }
    if (noSecurityCheck)
    {
        types.insert(NoSecurityCheckForVIP);
    }
    if (firstFly)
    {
        types.insert(FirstToFlyFirstToServe);
    }
    return types;
}

SimulationReport Simulator::simulateAllCases(const FileInfo &fileInfo)
{
    std::vector<CaseReport> caseReports;
    for (auto onlineTicketing : {false, true})
    {
        for (auto noSecurityCheckForVip : {false, true})
        {
            for (auto firstToFlyFirstToServe : {false, true})
            {
                // prepare simulation
                std::set<CaseType> caseTypes = getCaseTypes(onlineTicketing, noSecurityCheckForVip, firstToFlyFirstToServe);
                setFeatures(caseTypes);

                // simulate
                CaseReport caseReport = simulateCase(fileInfo);

                // add report
                caseReports.push_back(caseReport);
            }
        }
    }
    return SimulationReport(caseReports);
}
