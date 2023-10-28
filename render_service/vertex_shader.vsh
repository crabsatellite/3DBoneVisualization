#version 330 core
layout(location = 0) in vec3 vertexPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 clipMatrix;

out vec4 vertexColor;

void main()
{
    gl_Position =  clipMatrix * viewMatrix * modelMatrix * vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);
    vertexColor = vec4(clamp(vertexPosition, 0.0f, 1.0f), 1.0f);
};
