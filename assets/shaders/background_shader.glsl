#type vertex
#version 460 core

layout(location = 0) in vec2  inPos;
layout(location = 1) in vec2  inTexCoordinates;

layout (location = 0) out vec2  outTexCoordinates;

void main()
{
    gl_Position  = vec4(inPos, 0.f, 1.f);
    outTexCoordinates = inTexCoordinates;
}

#type fragment
#version 460 core

layout(location = 0) in vec2 outTexCoordinates;
layout(location = 0) out vec4 fColor;

uniform sampler2D textureSampler;

void main()
{
    fColor = texture(textureSampler, outTexCoordinates);
}