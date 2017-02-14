#version 410 core

// Variable in
layout(location = 0) in vec3 inputPosition;

//Variable out
layout(location = 0) out vec3 vsColor;

//Uniform in
uniform mat4 mvpMatrix;

void main(void)
{
    vsColor = vec3(1.0, 0.0, 0.0);
    gl_Position = mvpMatrix * vec4(inputPosition, 1.0);
}
