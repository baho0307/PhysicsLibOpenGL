#version 330 core
 layout (location = 0) in vec3 inPosition;
 uniform vec3 uPos;
 void main()
{
    gl_Position = vec4(inPosition+uPos, 1.0);
}