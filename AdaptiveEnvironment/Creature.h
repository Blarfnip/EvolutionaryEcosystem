#pragma once
#include "DNA.h"
#include "ofVec2f.h"
#include "EnvironmentObject.h"
#include "Food.h"

#define DEBUG_DISPLAY false

class Creature : public EnvironmentObject
{
private:
	DNA* dna;

	//ofVec2f pos;
	EnvironmentObject* targetObj;
	ofVec2f vel;
	ofVec2f acc;

	float maxSpeed;
	//float radius;
	//float sqrRadius;
	float attention;

	float maxLife;
	float life;

	float tOff;
	float reproductionTimestamp = 0.0;
	float reproductionCooldown = 16.0;

	int divisions = 32;
	float noiseScale = 0.5;


	void boundaries();
	void movement();
	float fourDimNoise(ofVec2f position);
	void drawFlowField();
	void drawSteering();
	bool isCollidingWith(EnvironmentObject* otherObj);
public:
	Creature();
	Creature(int xPos, int yPos);
	Creature::Creature(Creature* copyCreature);
	~Creature();

	void update();
	void draw();
	void foodInteractionDetection(vector<Food*>& interactionList, int& size);
	void creatureInteractionDetection(vector<Creature*>& interactionList, int& size, Creature*& possibleChild);
	void interactionDetection(vector<EnvironmentObject*>& interactionList, int& size, bool& doAction);

	//TODO Implement Reproduce
	Creature* reproduce();

	DNA* getDNA();
	bool getIsDead();

};

