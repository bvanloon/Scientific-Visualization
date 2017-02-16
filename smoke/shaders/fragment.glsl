#version 410 core

//Variable in
layout(location = 0) in float vsTextureCoordinate;

//Variable out
out vec4 fColor;

//Uniform in
uniform sampler1D colormap;

void main(void)
{
    fColor = texture(colormap, vsTextureCoordinate);
}
