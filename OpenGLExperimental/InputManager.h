#pragma once
class InputManager
{
public:
	unsigned char forward = 'w';
	unsigned char exit = 27;
	void Process(unsigned char key);

};

