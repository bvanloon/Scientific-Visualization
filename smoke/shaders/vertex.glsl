#version 410 core
//Definitions
struct rangeInfo {
    float minimum;
    float maximum;
};

// Variable in
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in float inputTextureCoordinate;

//Variable out
layout(location = 0) out float vsTextureCoordinate;

//Uniform in
uniform mat4 mvpMatrix;
uniform rangeInfo range;

float mapToUnitLength(float value, rangeInfo oldRange)
{
    float slope = 1/ (oldRange.maximum - oldRange.minimum);
    return slope * (value - oldRange.minimum);
}
void main(void)
{
    vsTextureCoordinate = mapToUnitLength(inputTextureCoordinate,range);
    gl_Position = mvpMatrix * vec4(inputPosition, 1.0);
}
