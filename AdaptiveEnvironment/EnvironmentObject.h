#pragma once
#include "ofVec2f.h"
#include "ofGraphics.h"
#include "typeinfo"
#include "string"
using std::vector;


class EnvironmentObject
{
private:
protected:
	ofVec2f pos;
	float radius;
	float sqrRadius;
	bool isDead = false;

public:
	EnvironmentObject() {};
	virtual ~EnvironmentObject() {};

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void interactionDetection(vector<EnvironmentObject*>& interactionList, int& size, bool& doAction) = 0;

	ofVec2f getPos() {
		return pos;
	}

	float getRadius() {
		return radius;
	}

	float getSqrRadius() {
		return sqrRadius;
	}

	float randomFloat() {
		return (float)rand() / RAND_MAX;
	}

	virtual bool getIsDead() = 0;
	void setIsDead(bool val) { isDead = val; }
};

