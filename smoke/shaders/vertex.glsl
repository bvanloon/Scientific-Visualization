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

float clampTextureCoordinates(float inputTextureCoordinate){
    float slopeMin = colorMapInfo.minimum * colorMapInfo.clampStart;
    float  slopeMax = colorMapInfo.maximum * colorMapInfo.clampEnd;

    //Clamping
    inputTextureCoordinate = max(inputTextureCoordinate, slopeMin);
    inputTextureCoordinate = min(inputTextureCoordinate, slopeMax);

    float slope = 1 / (slopeMax - slopeMin);
    return slope * (inputTextureCoordinate - slopeMin);

}

float scaleTextureCoordinates(float inputTextureCoordinate){
        float slope = 1 / (colorMapInfo.maximum - colorMapInfo.minimum);
        return slope * (inputTextureCoordinate - colorMapInfo.minimum);
}

float computeTextureCoordinate(float inputTextureCoordinate){
    if (colorMapInfo.clampingOn) {
        return clampTextureCoordinates(inputTextureCoordinate);
    }
    return scaleTextureCoordinates(inputTextureCoordinate);
}


//float mapToUnitLength(float value, rangeInfo oldRange, clampInfo clampValues)
//{
//    float slopeMin = oldRange.minimum;
//    float slopeMax = oldRange.maximum;

//    if (clampValues.clampingOn)
//    {
//        slopeMin = oldRange.minimum * clampValues.clampStart + oldRange.minimum;
//        slopeMax = oldRange.maximum * clampValues.clampEnd;

//        if (value < slopeMin)
//            value = slopeMin;

//        if (value > slopeMax)
//            value = slopeMax;
//    }


//}

void main(void)
{
    vsTextureCoordinate = computeTextureCoordinate(inputTextureCoordinate);
    gl_Position = mvpMatrix * vec4(inputPosition, 1.0);
}
