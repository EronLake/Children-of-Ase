#version 330 core

in vec4 oColor;
in vec2 oTextureCoords;
out vec4 zColor;

uniform sampler2D tex;

void main()
{
  zColor = texture(tex, oTextureCoords);
}
