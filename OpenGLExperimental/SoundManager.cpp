
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
	engine->play2D("breakout.mp3", true);

}
