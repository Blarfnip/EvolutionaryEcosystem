#include "ofApp.h"
#include "ofMath.h"
#include "../Creature.h"
#include "../Food.h"
#include "ofxGraph.h"
using std::vector;


#if DEBUG_DISPLAY
int creatureAmount = 1;
int foodAmount = 0;
#else
int creatureAmount = 25;
int foodAmount = 50;
#endif //DEBUG_DISPLAY
int simulationLoops = 1;
int loopCount = 0;
float foodSpawnPercentage = 0.05;

vector<Creature*> creatures;


vector<Food*> food;

ofxGraph dnaGraph;
ofxGraph objectCountGraph;
bool isDrawingGraph = false;
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(195, 215, 195);

	ofxGuiSetFillColor(ofColor(0, 0, 0));

	dnaGraph.setup("Average DNA Values");
	dnaGraph.setSize(800, 600);
	dnaGraph.setDx(1.0); // which means delta of time
	dnaGraph.setColor(ofColor::black);  // ofColor(255,255,255)
	dnaGraph.setLabel({ "Size","Speed","Max Life","Food Attention"});

	objectCountGraph.setup("Object Count");
	objectCountGraph.setSize(500, 300);
	objectCountGraph.setDx(1.0); // which means delta of time
	objectCountGraph.setColor(ofColor::black);  // ofColor(255,255,255)
	objectCountGraph.setLabel({ "Creatures","Food"});


	//ofSetFrameRate(60);

	for (int i = 0; i < creatureAmount; i++) {
		creatures.push_back(new Creature(((float)rand() / RAND_MAX) * ofGetViewportWidth(), ((float)rand() / RAND_MAX) * ofGetViewportHeight()));
	}


	for (int i = 0; i < foodAmount; i++) {
		food.push_back(new Food(((float)rand() / RAND_MAX) * ofGetViewportWidth(), ((float)rand() / RAND_MAX) * ofGetViewportHeight()));
	}

	
}

//--------------------------------------------------------------
void ofApp::update(){


	for (int loop = 0; loop < simulationLoops; loop++) {

		for (int i = 0; i < foodAmount; i++) {
			if (food[i]->getIsDead()) {
				delete ((food)[i]);
				(food).erase((food).begin() + i);
				(foodAmount)--;
			}
		}

		for (int i = 0; i < creatureAmount; i++) {
			(*creatures[i]).update();
			(*creatures[i]).foodInteractionDetection(food, foodAmount);
			Creature* possibleChild = nullptr;
			(*creatures[i]).creatureInteractionDetection(creatures, creatureAmount, possibleChild);

			if (possibleChild != nullptr) {
				creatures.push_back(possibleChild);
				creatureAmount++;
			}

			/*Creature* reproduceVal = (*creatures[i]).reproduce();
			if (reproduceVal != nullptr) {
				creatures.push_back(reproduceVal);
				creatureAmount++;
			}*/

			if ((*creatures[i]).getIsDead()) {
				/*food.push_back(new Food(creatures[i]->getPos().x, creatures[i]->getPos().y));
				foodAmount++;*/
				
				delete (creatures[i]);
				creatures.erase(creatures.begin() + i);
				creatureAmount--;
				
			}
		}


		if (((float)rand() / RAND_MAX) < foodSpawnPercentage) {
			food.push_back(new Food(((float)rand() / RAND_MAX) * ofGetViewportWidth(), ((float)rand() / RAND_MAX) * ofGetViewportHeight()));
			foodAmount++;
		}

		if (loopCount % 240 == 0) {
			//std::cout << "------------------------STATS------------------------" << std::endl;
			//std::cout << "Creature count: " << creatureAmount << std::endl;
			//std::cout << "Food count: " << foodAmount << std::endl;
			vector<float> objectCountValues;
			objectCountValues.push_back(creatureAmount);
			objectCountValues.push_back(foodAmount);
			objectCountGraph.add(objectCountValues);

			float avgSize = 0;
			float avgSpeed = 0;
			float avgMaxLife = 0;
			float avgFoodAttention = 0;
			for (int i = 0; i < creatureAmount; i++) {
				avgSize += (creatures[i]->getDNA()->getDNA()["size"]);
				avgSpeed += (creatures[i]->getDNA()->getDNA()["speed"]);
				avgMaxLife += (creatures[i]->getDNA()->getDNA()["max life"]);
				avgFoodAttention += (creatures[i]->getDNA()->getDNA()["food attention"]);
			}
			avgSize /= (float)creatureAmount;
			avgSpeed /= (float)creatureAmount;
			avgMaxLife /= (float)creatureAmount;
			avgFoodAttention /= (float)creatureAmount;
			vector<float> dnaValues;
			dnaValues.push_back(avgSize);
			dnaValues.push_back(avgSpeed);
			dnaValues.push_back(avgMaxLife);
			dnaValues.push_back(avgFoodAttention);
			dnaGraph.add(dnaValues);
			//std::cout << "Average Creature Size: " << avgSize << std::endl;
			//std::cout << "Average Creature Speed: " << avgSpeed << std::endl;
			//std::cout << "Average Creature Max Life: " << avgMaxLife << std::endl;
			//std::cout << "Average Creature Food Attention: " << avgFoodAttention << std::endl;
		}

		loopCount++;
		if (loopCount >= 1000000) {
			loopCount = 0;
		}
	}

}


//--------------------------------------------------------------
void ofApp::draw()
{
	for (int i = 0; i < foodAmount; i++) {
		(*food[i]).draw();
	}
	
	for (int i = 0; i < creatureAmount; i++) {
		(*creatures[i]).draw();
	}

	if (isDrawingGraph) {
		dnaGraph.draw();
		objectCountGraph.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == '1') {
		simulationLoops = 1;
	}
	else if (key == '2') {
		simulationLoops = 2;
	}
	else if (key == '3') {
		simulationLoops = 3;
	}
	else if (key == '4') {
		simulationLoops = 4;
	}
	else if (key == '5') {
		simulationLoops = 5;
	}
	else if (key == '6') {
		simulationLoops = 6;
	}
	else if (key == '7') {
		simulationLoops = 7;
	}
	else if (key == '8') {
		simulationLoops = 8;
	}
	else if (key == '9') {
		simulationLoops = 9;
	}
	else if (key == '0') {
		simulationLoops = 10;
	}
	else if (key == 'g') {
		isDrawingGraph = !isDrawingGraph;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	/*for (int i = 0; i < creatureAmount; i++) {
		(*creatures[i]).setTargetPos(x, y);
	}*/
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	/*for (int i = 0; i < creatureAmount; i++) {
		(*creatures[i]).setTargetPos(-1, -1);
	}*/
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
