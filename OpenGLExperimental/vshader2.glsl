#version 330 core

in vec4 vPosition;
in vec3 vNormal;

uniform mat4 ModelView,Projection;

out  vec4 vColor;



void main()
{


vec4 pos=Projection*ModelView*vPosition;
  gl_Position = pos;
	vColor=gl_Position;
}
