
#version 330 core
in vec4 vPosition;
uniform mat4 Model,View,Projection;
out vec3 vCoords3d;



void main()
{
    vCoords3d = vec3(vPosition);
	
  vec4 pos = transpose(mat4(mat3(transpose(View))))*(Projection )* vec4(vec3(vPosition.x,vPosition.y,vPosition.z),1.0);

    gl_Position = pos.xyww;
} 