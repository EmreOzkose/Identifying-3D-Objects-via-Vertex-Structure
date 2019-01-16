#version 330 core
out vec4 FragColor;
in vec3 vCoords3d;
uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, vCoords3d);
}