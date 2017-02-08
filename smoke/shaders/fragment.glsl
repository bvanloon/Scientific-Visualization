#version 410 core

//Variable in
layout(location = 0) in vec3 vsColor;

//Variable out
out vec4 fColor;

//Uniform in

void main(void)
{
    fColor = vec4(vsColor, 1.0);
}
