# version 330 core

in vec3 iColor;
in vec2 iTextureCoords;

out vec4 oColor;

uniform sampler2D tex;

void main()
{
  oColor = texture(tex, iTextureCoords);
}
