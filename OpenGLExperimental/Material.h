#pragma once
#include <Angel_commons/Angel.h>
class Material {

public:
	vec3 m_Color,m_Emission,m_Specular;
	GLfloat m_Smoothness;


	Material(vec3 color, vec3 specular)
	{
		m_Color = color;
		m_Specular = specular;
	}

	Material(vec3 color, vec3 specular,GLfloat smoothness)
	{
		m_Color = color;
		m_Smoothness = smoothness;
		m_Specular = specular;
	}
	Material() {
	}
};