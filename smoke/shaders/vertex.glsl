#version 410 core

// Variable in
layout(location = 0) in vec3 inputPosition;

//Variable out
layout(location = 0) out float vsTextureCoordinate;

//Uniform in
uniform mat4 mvpMatrix;

void main(void)
{
    vsTextureCoordinate = 0.5;
    gl_Position = mvpMatrix * vec4(inputPosition, 1.0);
}
