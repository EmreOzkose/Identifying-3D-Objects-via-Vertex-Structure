#include "Material.h"

void Material::ChangeSmoothness(GLfloat change)
{
	m_Smoothness += change;
}

void Material::ChangeSpecular(vec3 spec)
{
	m_Specular = spec;
}

void Material::ChangeColor(vec3 color)
{
	m_Color = color;
}
