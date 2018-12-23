#include "InputManager.h"
#include <Angel_commons/Angel.h>
void InputManager::Process(unsigned char key)
{
	if (key == exit)
		std::exit(0);
}
