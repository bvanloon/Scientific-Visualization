#version 410 core
//Definitions
struct colorMapInfoStruct {
    float minimum;
    float maximum;
    float clampStart;
    float clampEnd;
    bool clampingOn;
};

// Variable in
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in float inputTextureCoordinate;

//Variable out
layout(location = 0) out float vsTextureCoordinate;

//Uniform in
uniform mat4 mvpMatrix;
uniform colorMapInfoStruct colorMapInfo;

float mapToUnitRange(float value, float oldMin, float oldMax)
{
    float slope = 1 / (oldMax - oldMin);
    return slope * (value - oldMin);
}

float mapToRange(float value, float oldMin, float oldMax, float newMin, float newMax)
{
    float slope = (newMax - newMin) / ((oldMax - oldMin));
    return newMin + slope * (value - oldMin);
}

float clampTextureCoordinates(float inputTextureCoordinate){
    //Clamping
    inputTextureCoordinate = max(inputTextureCoordinate, colorMapInfo.clampStart);
    inputTextureCoordinate = min(inputTextureCoordinate, colorMapInfo.clampEnd);

    return mapToUnitRange(inputTextureCoordinate, colorMapInfo.clampStart, colorMapInfo.clampEnd);
}

float scaleTextureCoordinates(float inputTextureCoordinate){
        return mapToUnitRange(inputTextureCoordinate, colorMapInfo.minimum, colorMapInfo.maximum);
}

float computeTextureCoordinate(float inputTextureCoordinate){
    if (colorMapInfo.clampingOn) {
        return clampTextureCoordinates(inputTextureCoordinate);
    }
    return scaleTextureCoordinates(inputTextureCoordinate);
}

void main(void)
{
    vsTextureCoordinate = computeTextureCoordinate(inputTextureCoordinate);
    gl_Position = mvpMatrix * vec4(inputPosition, 1.0);
}
