#version 330 core

in vec4 vPosition;
in vec3 vNormal;
uniform mat4 Model,Projection,View;
uniform float time;
vec3 init_vel=vec3(0,10,0);
float g=-.2;
void main()
{
	vec4 pos;
	pos.x= vPosition.x+ init_vel.x*time;
	pos.y= vPosition.y+ init_vel.y*time + g*time*time / 2.0;
	pos.z= vPosition.z+ init_vel.z*time;
	pos.w=vPosition.w;
	gl_Position = Projection*View*Model*pos;



	

}

