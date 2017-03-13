#version 410 core

//Variable in
layout(location = 0) in float vsTextureCoordinate;

//Variable out
out vec4 fColor;

//Uniform in
uniform sampler1D colormap;

vec4 noLight(){
    return texture(colormap, vsTextureCoordinate);
}

void main(void)
{
    fColor = noLight();
}
