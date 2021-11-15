#include <iostream>
#include <set>

#define	que q->up
#define	qdw q->dw
#pragma once

using namespace std;

struct queue {
	set <int> up;
	set <int, greater<int>> dw;
};

class Elevator
{
public:
	Elevator(char id);

	char id;
	int cur;
	int tar;
	int dir;
	queue* q;

	void status(Elevator* minecart, int amount);
	void step(Elevator* minecart, int amount);
	void update(Elevator* minecart, int amount, char id, int target_floor, int direction);
	void pickup(Elevator* minecart, int amount, int current_floor, int target_floor);
	void request(Elevator* minecart, int amount, char id, int target_floor);
private:
	void error(int err);
};