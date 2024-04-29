#include <iostream>
#include <set>

class Elevator {
public:
	Elevator(u_int16_t elevatorId);
	~Elevator(void);

	u_int16_t elevatorId   {0};
	int16_t	  currentFloor {0};
	int16_t   targetFloor  {0};
	int16_t   direction    {0};

	struct {
		std::set <u_int16_t> up;
		std::set <u_int16_t, std::greater<u_int16_t>> down;
	} elevatorQueue;

	void getStatus(void);
	void makeStep(void);
	void setTargetFloor(int16_t target);
private:
	void callError(int16_t err);
};