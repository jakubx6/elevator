# Elevator
The elevator job simulator, was written in Microsoft Visual Studio Community 2019 Version 16.11.6, using the C++ language. 
The project consists of three files:
- main.cpp - the main program code;
- elevator.h - the header file of the Elevator class;
- elevator.cpp - the source file of Elevator class.

In order to run the program, you need to run 'make release' (check Makefile for references).

The program, after selecting the number of elevators, creates as many objects of Elevator class, which corresponds to next elevators and has:
- a unique ID;
- the value of the current floor;
- the value of the target floor;
- the direction of movement (1-top, -1-bottom, 0-going to the ground floor/free elevator);
- a queue structure, based on two set containers, to handle the queue for up and down travel.

Algorithm handling elevator selection for pickup method using percentage occupancy:
1. From 0% - select a free elevator to handle the call, break if yes;
2. From 80% - add the request to the elevator whose sum of the difference between the last floor of the current queue and the current floor of the call, and the size of the current queue, is the smallest.

Compared to the first-come, first-serve method, the above algorithm, always uses 100% of the available elevators, in an optimal way.The second step allows to select the elevator that will be the fastest available, after its queue for a given elevator direction has ended.
