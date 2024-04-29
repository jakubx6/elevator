#include <iostream>
#include <string>
#include <vector>

#include "Elevator.h"

using std::cin, std::cout;

inline bool isNumber(const std::string &s);
bool checkElevatorNumer(const std::string &s, const int16_t max);
uint16_t pickupAlgorithm(std::vector <Elevator*> &base, const std::string &first);

int main() {
    constexpr char coutBrake[] = "==========\n";
    constexpr char coutSetAmount[] = "Set amount of elevator cabs (1-16): ";
    constexpr char coutSelectState[] = "(1) Step; (2) Pickup; (3) Request; (4) Status; (5) Close\nChoose: ";
    constexpr int16_t maxElevatorId = 16;

    std::string firstBuffer {0};
    std::string secondBuffer {0};

    cout << "Elevator\n";
    do {
        cout << coutBrake << coutSetAmount;
        cin >> firstBuffer;
    } while(!checkElevatorNumer(firstBuffer, maxElevatorId));
    int16_t elevatorNumber = stoi(firstBuffer);

    std::vector <Elevator*> elevatorBase;
    for(u_int8_t id = 0; id < elevatorNumber; id++) {
        elevatorBase.push_back(new Elevator(id));
    }

    cout << coutBrake;
    for(auto elevator : elevatorBase) {
        elevator->getStatus();
    }

    int16_t parameter;
    bool loop = true;
    do {
        do {
            cout << coutBrake << coutSelectState;
            cin >> firstBuffer;
            cout << coutBrake;
        } while(!isNumber(firstBuffer));
        parameter = stoi(firstBuffer);

        switch(parameter) {
        case 1:
            for(auto elevator : elevatorBase) {
                elevator->makeStep();
                elevator->getStatus();
            }
            break;
        case 2:
            do {
                cout << "Pickup\nSet current floor: ";
                cin >> firstBuffer;
                cout << coutBrake;
            } while(!isNumber(firstBuffer));

            parameter = pickupAlgorithm(elevatorBase, firstBuffer);
            cout<<"Elevator no: "<<parameter<<".\n";
            break;
        case 3:
            do {
                cout << "Request\nSet elevator ID: ";
                cin >> firstBuffer;
                cout << "Set target floor: ";
                cin >> secondBuffer;
            } while(!checkElevatorNumer(firstBuffer, elevatorNumber) || !isNumber(secondBuffer));

            elevatorBase[stoi(firstBuffer) - 1]->setTargetFloor(stoi(secondBuffer));
            break;
        case 4:
            for(auto elevator : elevatorBase) {
                elevator->getStatus();
            }
            break;
        case 5:
            loop = false;
        }
    } while(loop);

    for(auto elevator : elevatorBase) {
        delete elevator;
    }
    return 0;
}

inline bool isNumber(const std::string &s) {
    return (s.find_first_not_of("-0123456789") == std::string::npos);
}

bool checkElevatorNumer(const std::string &s, const int16_t max) {
    bool result = true;
    result = isNumber(s);
    
    if(result) {
        int16_t buff = stoi(s);
        if(buff < 1 || buff > max) {
            result = false;
        }
    }
    return result;
}

uint16_t pickupAlgorithm(std::vector <Elevator*> &base, const std::string &first) {
    int16_t current = stoi(first);
    int16_t dir = (current > 0 ? -1 : 1);
    uint16_t counter = 0;
    for(auto elevator : base) {
        counter += abs(elevator->direction);
    }
    counter = counter / base.size() * 100;
    counter = (counter >= 50) ? 50 : 0;

    uint16_t min = ~0;

    switch(counter) {
    case 0:
        for(auto elevator : base) {
            if(elevator->direction == 0) {
                cout<<"90\n";
                elevator->targetFloor = current;
                elevator->direction = -1 * dir;
                counter = elevator->elevatorId;
                break;
            }
        }
        if(counter != 0)
            break;
    case 80:
        if(dir == 1) {
            for(auto elevator : base) {
                if(elevator->direction == dir && elevator->currentFloor <= current) {
                    if(min <= abs(elevator->currentFloor - current) + elevator->elevatorQueue.up.size()) {
                        min = abs(elevator->currentFloor - current) + elevator->elevatorQueue.up.size();
                        counter = elevator->elevatorId;
                    }                    
                }
            }
            if(min != (uint16_t) ~0) {
                base[counter]->elevatorQueue.up.insert(current);
                base[counter]->elevatorQueue.up.insert(base[counter]->targetFloor);
                base[counter]->targetFloor = *base[counter]->elevatorQueue.up.begin();
                base[counter]->elevatorQueue.up.erase(*base[counter]->elevatorQueue.up.begin());
                counter = base[counter]->elevatorId;
                break;
            }
        } else if(dir == -1) {
            for(auto elevator : base) {
                if(elevator->direction == dir && elevator->currentFloor >= current) {
                    if(min <= abs(elevator->currentFloor - current) + elevator->elevatorQueue.down.size()) {
                        min = abs(elevator->currentFloor - current) + elevator->elevatorQueue.down.size();
                        counter = elevator->elevatorId;
                    }

                }
            }
            if(min != (uint16_t) ~0) {
                base[counter]->elevatorQueue.down.insert(current);
                base[counter]->elevatorQueue.down.insert(base[counter]->targetFloor);
                base[counter]->targetFloor = *base[counter]->elevatorQueue.down.begin();
                base[counter]->elevatorQueue.down.erase(*base[counter]->elevatorQueue.down.begin());
                counter = base[counter]->elevatorId;
                break;
            }
        }
    }

    return counter;
}
