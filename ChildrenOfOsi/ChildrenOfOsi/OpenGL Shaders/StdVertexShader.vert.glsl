#version 330 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iColor;
layout (location = 2) in vec2 iTextureCoords;

out vec3 oColor;
out vec2 oTextureCoords;

void main()
{
  gl_Position = vec4(iPosition, 1.0F);
  oColor = iColor;
  oTextureCoords = oTextureCoords;
}
