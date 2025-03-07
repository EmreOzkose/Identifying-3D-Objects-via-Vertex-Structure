
#include <irrKlang.h>

using namespace irrklang;


class SoundManager {
public:
	ISoundEngine* engine = createIrrKlangDevice();

	int soundCheck();
	ISound *sound_background();
	void stopAllSounds();
	ISound *background_music;

	SoundManager() {
		//background_music = sound_background();
	}

};


/*
	Observations: Although music is short, it will be repeated. Because second parameter is 'loop parameter'
*/


/*
Install irrklang:
1. Download from https://www.ambiera.com/irrklang/downloads.html
2. copy include and lib files to your project
3. addd irrKlang.lib as a linker
4. copy .dll files
More info: https://learnopengl.com/In-Practice/2D-Game/Audio
*/