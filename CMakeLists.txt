cmake_minimum_required(VERSION 2.8)

project(project2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(PROJECT_FILES Simulator.cpp CaseReport.cpp SimulationReport.cpp GlobalComparer.cpp QueueComparer.cpp Common.cpp)

add_executable(project2 main.cpp ${PROJECT_FILES})
