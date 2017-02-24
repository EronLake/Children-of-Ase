#version 330 core

in vec2 iTexCoords;

out vec4 oColor;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, iTexCoords).r);
  oColor = vec4(textColor, 1.0) * sampled;
}
