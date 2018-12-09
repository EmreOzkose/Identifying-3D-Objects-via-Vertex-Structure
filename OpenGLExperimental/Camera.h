

#include "Object.h"
class Camera :public Object
{
public:
	Camera() : Object(&str[0u]) {

	}
private:
	std::string str = "MainCamera";
};
