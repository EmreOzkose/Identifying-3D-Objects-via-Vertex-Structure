#version 150
in vec4 vColor; 
out vec4  fColor;
void main()
{
    fColor = vec4(gl_FragCoord);
}
