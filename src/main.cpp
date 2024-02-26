#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "elevator.h"

using std::cin, std::cout;

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

u_int16_t pickup(std::vector <Elevator*> &base, const std::string &first, const std::string &second) {
    int16_t dir = stoi(second);
    if(dir == 0)
        return 0;

    int16_t current = stoi(first);
    u_int16_t counter = 0;
    for(auto elevator : base) {
        counter += abs(elevator->direction);
    }
    counter = counter / base.size() * 100;
    counter = (counter >= 90) ? 90 : (counter >= 50) ? 50 : 0;

    u_int16_t min = ~0;

    switch(counter) {
    case 0:
        cout<<"pick minecart from 0\n";
        for(auto elevator : base) {
            if(elevator->direction == 0) {
                elevator->targetFloor = current;
                elevator->direction = -1 * dir;
                counter = elevator->elevatorId;
                break;
            }
        }
    case 50:
    case 90:
        cout<<"pick minecart on the road\n";
        if(dir == 1) {
            for(auto elevator : base) {
                if(elevator->direction == dir && elevator->currentFloor <= current) {
                    if(min <= abs(elevator->currentFloor - current) + elevator->elevatorQueue.up.size()) {
                        min = abs(elevator->currentFloor - current) + elevator->elevatorQueue.up.size();
                        counter = elevator->elevatorId;
                    }                    
                }
            }
            if(min != (u_int16_t) ~0) {
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
            if(min != (u_int16_t) ~0) {
                base[counter]->elevatorQueue.down.insert(current);
                base[counter]->elevatorQueue.down.insert(base[counter]->targetFloor);
                base[counter]->targetFloor = *base[counter]->elevatorQueue.down.begin();
                base[counter]->elevatorQueue.down.erase(*base[counter]->elevatorQueue.down.begin());
                counter = base[counter]->elevatorId;
                break;
            }
        }
    case 100:
        cout<<"set to last\n";
        if(dir > 0) {
            base.back()->elevatorQueue.up.insert(current);
        }
        else {
            base.back()->elevatorQueue.down.insert(current);
        }
        counter = base.back()->elevatorId;
    }

    return counter;
}

int main() {
    constexpr char coutBrake[] = "==========\n";
    constexpr char coutSetAmount[] = "Set amount of elevator cabs (1-16): ";
    constexpr char coutSelectState[] = "(1) Step; (2) Pickup; (3) Request; (4) Status; (5) Close\nChoose: ";
    constexpr int16_t maxElevatorId = 16;

    std::string cinBuffer;
    cout << "Elevator\n";
    do {
        cout << coutBrake << coutSetAmount;
        cin >> cinBuffer;
    } while(!checkElevatorNumer(cinBuffer, maxElevatorId));
    int16_t elevatorNumber = stoi(cinBuffer);

    std::vector <Elevator*> elevatorBase;
    for(u_int8_t id = 0; id < elevatorNumber; id++) {
        elevatorBase.push_back(new Elevator(id));
    }

    cout << coutBrake;
    for(auto elevator : elevatorBase) {
        elevator->getStatus();
    }

    std::string firstBuffer {0};
    std::string secondBuffer {0};
    u_int16_t switchPar;
    bool loop = true;
    do {
        cout << coutBrake << coutSelectState;
        cin >> switchPar;
        cout << coutBrake;

        switch(switchPar) {
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
                cout << "Set direction: ";
                cin >> secondBuffer;
                cout << coutBrake;
            } while(!isNumber(firstBuffer) || !isNumber(secondBuffer));

            switchPar = pickup(elevatorBase, firstBuffer, secondBuffer);
            cout<<"Elevator no: "<<switchPar<<".\n";
            break;
        case 3:
            do {
                cout << "Request\nSet elevator ID: ";
                cin >> firstBuffer;
                cout << "Set target floor: ";
                cin >> secondBuffer;
                cout << coutBrake;
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
