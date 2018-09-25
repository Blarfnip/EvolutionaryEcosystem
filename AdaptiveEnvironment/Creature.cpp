#include "Creature.h"
#include "DNA.h"
#include "ofGraphics.h"
#include "ofMath.h"
#include "ofUtils.h"
#include "Food.h"

Creature::Creature()
{
	dna = new DNA();

	pos = ofVec2f(0, 0);
	targetObj = nullptr;
	vel = ofVec2f(0, 0);
	acc = ofVec2f(0, 0);

	maxSpeed = 5 * ((*dna).getDNA()["speed"]);
	radius = ((*dna).getDNA()["size"] * 70 + 10) / 2.0;
	sqrRadius = radius * radius;

	attention = ((*dna).getDNA()["food attention"]);

	tOff = randomFloat() * 1000;

	maxLife = ((*dna).getDNA()["max life"] * 125.0 + 10.0);
	life = maxLife;
}

Creature::Creature(int xPos, int yPos)
{
	dna = new DNA();

	pos = ofVec2f(xPos, yPos);
	targetObj = nullptr;
	vel = ofVec2f(0, 0);
	acc = ofVec2f(0, 0);

	maxSpeed = 5 * ((*dna).getDNA()["speed"]);
	radius = ((*dna).getDNA()["size"] * 70 + 10) / 2.0;
	sqrRadius = radius * radius;

	attention = ((*dna).getDNA()["food attention"]);

	tOff = randomFloat() * 1000;

	maxLife = ((*dna).getDNA()["max life"] * 125.0 + 10.0);
	life = maxLife;
	
}

Creature::Creature(Creature* copyCreature)
{
	dna = (*(*copyCreature).getDNA()).copy();
	(*dna).mutate(0.03);

	pos = (*copyCreature).getPos();
	targetObj = nullptr;
	vel = ofVec2f(0, 0);
	acc = ofVec2f(0, 0);

	maxSpeed = 5 * ((*dna).getDNA()["speed"]);
	radius = ((*dna).getDNA()["size"] * 70 + 10) / 2.0;
	sqrRadius = radius * radius;

	attention = ((*dna).getDNA()["food attention"]);

	tOff = randomFloat() * 1000;

	maxLife = ((*dna).getDNA()["max life"] * 125.0 + 10.0);
	life = maxLife;
}


Creature::~Creature()
{
}

void Creature::update()
{
	tOff += 0.001;
	movement();
	boundaries();

	

#if !DEBUG_DISPLAY
	life -= 0.1;
#endif //DEBUG_DISPLAY
}

void Creature::movement() {
	//FLOWFIELD
	float noiseVal = ((2 * fourDimNoise(pos)) - 1) * TWO_PI;
	ofVec2f flowVel = ofVec2f(cos(noiseVal), sin(noiseVal));
	flowVel *= maxSpeed;

	//STEERING
	if (targetObj != nullptr && pos.squareDistance(targetObj->getPos()) <= 1) {
		targetObj = nullptr;
	}

	
	ofVec2f desired = pos;
	float weightedAttenton = 0;
	if (targetObj != nullptr) {
		desired = targetObj->getPos() - pos;
		desired.normalize();
		desired *= maxSpeed;
		
		float distance = pos.squareDistance(targetObj->getPos());
		
		if (distance < 300000) {
			weightedAttenton = 1.0 - (distance / 300000.0);
			weightedAttenton *= attention;
		}
	}

	

	vel = weightedAttenton * desired + (1 - weightedAttenton) * flowVel;

	//MODIFYING POSITION
	pos += vel;
}


float Creature::fourDimNoise(ofVec2f position) {
	ofVec2f adjustedPos = ofVec2f((2.0 * (1.0 * position.x / ofGetViewportWidth())) - 1, (2.0 * (1.0 * position.y / ofGetViewportHeight())) - 1);
	adjustedPos = adjustedPos * PI;
	float ay = sin(adjustedPos.x);
	float ax = cos(adjustedPos.x);
	float by = sin(adjustedPos.y);
	float bx = cos(adjustedPos.y);

	float val = ofNoise(tOff + noiseScale * ay, tOff + noiseScale * ax, tOff + noiseScale * by, tOff + noiseScale * bx);
	return val;
}

void Creature::draw()
{
#if DEBUG_DISPLAY
	drawFlowField();
	drawSteering();
#endif //DEBUG_DISPLAY
	
	ofSetColor(0, 50, 255, 255 * (life / maxLife));
	ofFill();
	ofDrawEllipse(pos.x, pos.y, radius * 2.0, radius * 2.0);
	//ofDrawRectangle(pos.x - radius, pos.y - radius, radius * 2, radius * 2);
}

#if DEBUG_DISPLAY
void Creature::drawFlowField() {
	int cols = ofGetViewportWidth() / divisions;
	int rows = ofGetViewportHeight() / divisions;
	float xNoiseOff = 0;
	for (int i = 0; i <= cols; i += 1) {
		float yNoiseOff = 0;
		for (int k = 0; k <= rows; k += 1) {
			ofSetColor(255);
			ofSetLineWidth(2);
			float noiseVal = fourDimNoise(ofVec2f(i * divisions, k * divisions));
			ofSetColor(0, 0, 0, noiseVal * 255);
			ofDrawRectangle(i * divisions, k * divisions, divisions, divisions);
			ofVec2f posVel = ofVec2f(cos(noiseVal * TWO_PI), sin(noiseVal * TWO_PI));
			ofDrawLine(ofVec2f(i * divisions, k * divisions), ofVec2f(i * divisions, k * divisions) + posVel * 20);

			yNoiseOff += 0.1;
		}
		xNoiseOff += 0.1;
	}
}

void Creature::drawSteering() {
	ofSetColor(255, 255, 0, 255);
	ofSetLineWidth(2);
	ofDrawLine(pos, pos + vel * 30);
	ofSetColor(0, 255, 255, 255);
	if (targetObj != nullptr) {
		ofVec2f desired = targetObj->getPos() - pos;
		desired.normalize();
		desired *= maxSpeed;
		ofDrawLine(pos, pos + desired * 30);
	}
	
}
#endif //DEBUG_DISPLAY

Creature* Creature::reproduce() {
	if (randomFloat() < 0.0007) {
		return new Creature(this);
	}
	else {
		return nullptr;
	}
}

void Creature::boundaries()
{
	pos.x = (pos.x > ofGetViewportWidth()) ? pos.x - ofGetViewportWidth() : pos.x;
	pos.x = (pos.x < 0) ? pos.x + ofGetViewportWidth() : pos.x;
	pos.y = (pos.y > ofGetViewportHeight()) ? pos.y - ofGetViewportHeight() : pos.y;
	pos.y = (pos.y < 0) ? pos.y + ofGetViewportHeight() : pos.y;
}

void Creature::interactionDetection(vector<EnvironmentObject*> *interactionList, int* size)
{
	for (int i = 0; i < *size; i++) {
		if (pos.squareDistance((*(*interactionList)[i]).getPos()) < sqrRadius + (*(*interactionList)[i]).getSqrRadius()) { //Collide
			//std::cout << typeid((*(*interactionList)[i])).name() << std::endl;
			if (typeid((*(*interactionList)[i])).name() == std::string("class Food") && (*interactionList)[i]->getIsDead() == false) {
				//std::cout << "FOOD INTERACTION" << std::endl;
				//dynamic_cast<Food*>((*interactionList)[i])->setHasBeenEaten(true);
				(*interactionList)[i]->setIsDead(true);
				targetObj = nullptr;
				//delete ((*interactionList)[i]);
				//(*interactionList).erase((*interactionList).begin() + i);
				//(*size)--;
				life += 50.0;
				if (life > maxLife) {
					life = maxLife;
				}
			}
			else if (typeid((*(*interactionList)[i])).name() == std::string("class Creature")) {

			}
		}
		else {
			if ((targetObj == nullptr || pos.squareDistance((*(*interactionList)[i]).getPos()) < pos.squareDistance(targetObj->getPos())) && (*interactionList)[i]->getIsDead() == false) {
				targetObj = (((*interactionList)[i]));

			}
		}
		
	}
}


DNA* Creature::getDNA() {
	return (dna);
}

bool Creature::getIsDead() {
	if (life < 0.0) {
		isDead = true;
	}
	else {
		isDead = false;
	}
	return isDead;
}
