#include "Food.h"



Food::Food()
{
	pos = ofVec2f(0, 0);
	radius = 5;
}

Food::Food(int startX, int startY)
{
	pos = ofVec2f(startX, startY);
	radius = 5;
	sqrRadius = radius * radius;
}


Food::~Food()
{
}

void Food::draw() {
	ofFill();
	ofSetColor(75, 200, 75);
	ofDrawRectangle(pos.x - radius, pos.y - radius, radius * 2, radius * 2);
}

void Food::update() {

}

void Food::interactionDetection(vector<EnvironmentObject*> *interactionList, int* size) {

}

bool Food::getIsDead() {
	return isDead;
}
