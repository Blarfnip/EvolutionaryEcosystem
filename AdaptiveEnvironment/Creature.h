#pragma once
#include "DNA.h"
#include "ofVec2f.h"
#include "EnvironmentObject.h"

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

	int divisions = 32;
	float noiseScale = 0.5;


	void boundaries();
	void movement();
	float fourDimNoise(ofVec2f position);
	void drawFlowField();
	void drawSteering();
public:
	Creature();
	Creature(int xPos, int yPos);
	Creature::Creature(Creature* copyCreature);
	~Creature();

	void update();
	void draw();
	void interactionDetection(vector<EnvironmentObject*> *interactionList, int* size);

	//TODO Implement Reproduce
	Creature* reproduce();

	DNA* getDNA();
	bool getIsDead();

};

