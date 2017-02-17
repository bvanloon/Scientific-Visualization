#version 410 core

// Variable in
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in float inputTextureCoordinate;

//Variable out
layout(location = 0) out float vsTextureCoordinate;

//Uniform in
uniform mat4 mvpMatrix;

float mapToUnitLength(float value, float oldMin, float oldMax)
{
    float slope = 1/ (oldMax - oldMin);
    return slope * (value - oldMin);
}
void main(void)
{
    vsTextureCoordinate = mapToUnitLength(inputTextureCoordinate,5,10);
    gl_Position = mvpMatrix * vec4(inputPosition, 1.0);
}
