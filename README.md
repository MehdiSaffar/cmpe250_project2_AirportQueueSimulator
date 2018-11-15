# CMPE250 2018 Fall Project 2


## Description
Implementing a program that simulates the luggage and security queues of an airport under different constraints.
Each passenger has properties:
 - Arrival time
 - Flight time
 - Wait time in luggage counter
 - Wait time in security counter
 - Whether the passenger is VIP or not
 - Whether the passenger has luggage or not

There are three types of constraints (or features):
 - VIP Program: VIP passengers skip security queue
 - Online ticketing: Passenger without luggage skip luggage queue
 - First-fly first-serve: Passenger who fly first are more prioritary in queue.

The cases simulated are all the possible combinations of those three features, therefore for each input we have 8 cases.
Each case report contains the average wait time of passenger and how many passengers miss their flight

The solution uses a global event queue as well as two seperates priority queues for security and luggage queues.

Please check out Project2.pdf for more in depth description of the project.

Due date: 24.10.2017 23:59

Due date is a strict due date!


## How to compile
In a terminal, call commands:

>cmake CMakeLists.txt && make

Make sure the executable is produced.

Then you can test the project with the command:

>./project2 inputFile outputFile
