#version 410 core

//Variable in
layout(location = 0) in float vsTextureCoordinate;

//Variable out
out vec4 fColor;

//Uniform in
uniform sampler1D colormap;
uniform int lightModel;

void noLight(){
    fColor =  texture(colormap, vsTextureCoordinate);
}

void phongLight(){
    fColor = vec4(1.0, 0.0, 0.0, 1.0);
}

void main(void)
{
    if(lightModel == 0) noLight();
    if(lightModel == 1) phongLight();
}
