#version 410 core

// Variable in
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputColor;

//Variable out
layout(location = 0) out vec3 vsColor;

//Uniform in

void main(void)
{
//    vsColor = inputColor;
    vsColor = vec3(1.0, 0.0, 0.0);
    gl_Position = vec4(inputPosition, 1.0);
}
