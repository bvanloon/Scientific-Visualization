#version 410 core

// Variable in
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputColor;

//Variable out
layout(location = 0) out vec3 vsColor;

//Uniform in

void main(void)
{
    vsColor = inputColor;
    gl_Position = mvpMatrix * vec4(inputPosition, 1.0);
}
