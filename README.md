# Elevator
The elevator job simulator, was written in Microsoft Visual Studio Community 2019 Version 16.11.6, using the C++ language. 
The project consists of three files:
- main.cpp - the main program code;
- elevator.h - the header file of the Elevator class;
- elevator.cpp - the source file of Elevator class.

In order to run the program, you need to compile main.cpp file.

The program, after selecting the number of elevators, creates as many objects of Elevator class, which corresponds to next elevators and has:
- a unique ID;
- the value of the current floor;
- the value of the target floor;
- the direction of movement (1-top, -1-bottom, 0-going to the ground floor/free elevator);
- a queue structure, based on two set containers, to handle the queue for up and down travel.

Elevator class methods:
1. Step - performs the simulation step;
2. Pickup - after providing input parameters (current floor number, target  floor number), selects an elevator to handle the request;
3. Request - after providing input parameters (elevator id, current floor number), adds the call to the queue of a specific elevator;
4. Update - after providing input parameters (elevator id, target floor number, direction of travel), changes these values for a specific elevator;
5. Status - displays the current status of all elevators, in order: elevator id, current floor value, target floor value, direction of travel.

Algorithm handling elevator selection for Pickup method:
1. Select a free elevator to handle the call, break if yes;
2. Add the request to the elevator queue that will pass the current floor and has a compatible direction of travel, break if yes;
3. Add the request to the elevator whose sum of the difference between the last floor of the current queue and the current floor of the call, and the size of the current queue, is the smallest.

Compared to the first-come, first-serve method, the above algorithm, always uses 100% of the available elevators, in an optimal way. For the second step, the selected elevator will always pass the floors from the request, in  correct travel direction. The third step allows to select the elevator that will be the fastest available, after its queue for a given elevator direction has ended.
