
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


void SoundManager::stopAllSounds() {
	engine->stopAllSounds();
}