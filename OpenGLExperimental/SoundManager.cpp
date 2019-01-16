
#include "SoundManager.h"
#include <iostream>

using namespace std;


int SoundManager::soundCheck() {
	if (!engine) {
		cout << "Could not startup engine\n" << endl;
		return 1; // error starting up the engine
	}

	return 0;
}

void SoundManager::sound_background(){
	engine->play2D("audio/background.mp3", true);
}

void SoundManager::sound_airplane_departure() {
	engine->play2D("audio/airplane_departure.mp3", true);
}

void SoundManager::sound_robot() {
	engine->play2D("audio/robot.mp3", true);
}
