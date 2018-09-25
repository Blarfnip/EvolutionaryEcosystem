#pragma once
#include "EnvironmentObject.h"

class Food : public EnvironmentObject
{
private:
public:
	Food();
	Food(int startX, int startY);
	~Food();

	void draw();
	void update();
	void interactionDetection(vector<EnvironmentObject*> *interactionList, int* size);
	//TODO add a hasBeenEaten flag, and a delayed deletion to allow for food tracking
	bool getIsDead();
};

