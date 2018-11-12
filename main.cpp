#include <iostream>
#include <queue>
#include <fstream>
#include <assert.h>
#include <sstream>
#include "Common.hpp"
#include "Airport.hpp"
#include "QueueComparer.hpp"
#include "GlobalComparer.hpp"
#include "Simulator.hpp"
#include "FileInfo.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Please execute with `./project2 inputFile output`" << std::endl;
        return -1;
    }
    std::string inputFilePath(argv[1]);
    std::string outputFilePath(argv[2]);
    FileInfo fileInfo = parseFileContent(readAllLines(inputFilePath));

    Simulator simulator(fileInfo.airport);
    SimulationReport simulationReport = simulator.simulateAllCases(fileInfo);
    std::vector<std::string> outputLines = simulationReportToLines(simulationReport);
    writeAllLines(outputFilePath, outputLines);
    return 0;
}
