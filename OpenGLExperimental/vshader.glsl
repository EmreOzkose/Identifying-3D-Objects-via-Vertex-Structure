#version 330 core

in vec4 vPosition;


uniform mat4 MVP;

out  vec4 vColor;



void main()
{



  gl_Position = vPosition;
  vColor=gl_Position;
}
