#version 410 core

//Variable in
layout(location = 0) in float vsTextureCoordinate;
layout(location = 1) in vec3 vsNormal;
layout(location = 2) in vec3 vsPosition;

//Variable out
out vec4 fColor;

//Uniform in
uniform sampler1D colormap;
uniform int lightModel;

vec3 unitVectorToColor(vec3 vector){
        return (vector + vec3(1)) / 2.0;
}

void noLight(){
    fColor =  texture(colormap, vsTextureCoordinate);
}

void phongLight(){
    fColor = vec4(unitVectorToColor(normalize(vsPosition)), 1.0);
}

void main(void)
{
    if(lightModel == 0) noLight();
    if(lightModel == 1) phongLight();
}
