#version 330 core

in vec4 vPosition;
in vec3 vNormal;

uniform mat4 MVP;

out  vec4 vColor;



void main()
{


vec4 pos=MVP*vPosition;
  gl_Position = pos;
  if(mod(ceil(pos.x+pos.y+pos.z),2)==0)
	vColor=vec4(1,0,0,1);
else
	vColor=vec4(1,1,0,1);
	vColor=vec4(pos.x+pos.y+pos.z*5);
}
