#include "elevator.h"

//Constructor
Elevator::Elevator(u_int16_t id) {
    this->elevatorId = ++id;
};

//Destructor
Elevator::~Elevator(void) {
};

void Elevator::getStatus(void) {
    std::cout << this->elevatorId << ". " << this->currentFloor << " " << this->targetFloor << " " << this->direction << std::endl;
}

void Elevator::makeStep(void) {
    //step current to tagret
    if(this->targetFloor != this->currentFloor) {
        if(this->direction > 0) {
            this->currentFloor++;
        }
        else if(this->direction < 0) {
            this->currentFloor--;
        }
        else if(this->direction == 0) {
            if(this->currentFloor > 0) {
                this->currentFloor--;
            }
            else {
                this->currentFloor++;
            }
        }
    }
    //get next target, direction up
    else if(this->targetFloor == this->currentFloor && this->direction == 1 && this->elevatorQueue.up.size() > 0) {
        this->targetFloor = *this->elevatorQueue.up.begin();
        this->elevatorQueue.up.erase(*this->elevatorQueue.up.begin());
    }
    //get next target, direction down
    else if(this->targetFloor == this->currentFloor && this->direction == -1 && this->elevatorQueue.down.size() > 0) {
        this->targetFloor = *this->elevatorQueue.down.begin();
        this->elevatorQueue.down.erase(*this->elevatorQueue.down.begin());
    }//get next target, direction up to down
    else if(this->targetFloor == this->currentFloor && this->direction == 1 && this->elevatorQueue.down.size() > 0) {
        this->direction = -1;
        this->targetFloor = *this->elevatorQueue.down.begin();
        this->elevatorQueue.down.erase(*this->elevatorQueue.down.begin());
    }//get next target, direction down to up
    else if(this->targetFloor == this->currentFloor && this->direction == -1 && this->elevatorQueue.up.size() > 0) {
        this->direction = 1;
        this->targetFloor = *this->elevatorQueue.up.begin();
        this->elevatorQueue.up.erase(*this->elevatorQueue.up.begin());
    }
    //go to 0
    else if(this->currentFloor != 0) {
        this->targetFloor = 0;
        this->direction = 0;
    }
    else if(this->currentFloor == 0) {
        this->direction = 0;
    }
    else {
        callError(1);
    }
}

void Elevator::setTargetFloor(int16_t target) {
    int16_t targetDir = 1;
    if(this->currentFloor > target) {
        targetDir = -1;
    }

    if(this->direction == 0) {
        this->direction = targetDir;
        this->targetFloor = target;
    }
    else if(targetDir == 1) {
        this->elevatorQueue.up.insert(target);
    }
    else {
        this->elevatorQueue.down.insert(target);
    }
}

void Elevator::callError(int16_t err) {
    std::cout << "callError " << err << std::endl;
    system("pause");
}