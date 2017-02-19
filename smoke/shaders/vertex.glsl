#version 410 core
//Definitions
struct rangeInfo {
    float minimum;
    float maximum;
};

struct clampInfo {
    bool clampingOn;
    float clampStart;
    float clampEnd;
};


// Variable in
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in float inputTextureCoordinate;

//Variable out
layout(location = 0) out float vsTextureCoordinate;

//Uniform in
uniform mat4 mvpMatrix;
uniform rangeInfo range;
uniform clampInfo clamping;

float mapToUnitLength(float value, rangeInfo oldRange, clampInfo clampValues)
{
    float slopeMin = oldRange.minimum;
    float slopeMax = oldRange.maximum;

    if (clampValues.clampingOn)
    {
        slopeMin = oldRange.minimum * clampValues.clampStart + oldRange.minimum;
        slopeMax = oldRange.maximum * clampValues.clampEnd;

        if (value < slopeMin)
            value = slopeMin;

        if (value > slopeMax)
            value = slopeMax;
    }

    float slope = 1/ (slopeMax - slopeMin);
    return slope * (value - slopeMin);
}

void main(void)
{
    vsTextureCoordinate = mapToUnitLength(inputTextureCoordinate, range, clamping);
    gl_Position = mvpMatrix * vec4(inputPosition, 1.0);
}
