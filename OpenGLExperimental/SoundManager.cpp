
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

ISound *SoundManager::sound_background() {
	return engine->play2D("Sounds/background.mp3", true, false, true);
}

void SoundManager::sound_airplane_departure() {
	engine->play2D("Sounds/airplane_departure.mp3", false);
}

void SoundManager::sound_robot() {
	engine->play2D("Sounds/robot.mp3", false);
}

void SoundManager::stopAllSounds() {
	engine->stopAllSounds();
}