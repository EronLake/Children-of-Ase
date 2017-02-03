# version 330 core

uniform vec3 iColor;
uniform vec2 iTextureCoords;

out vec4 oColor;

uniform sampler2D tex;

void main()
{
  oColor = texture(tex, iTextureCoords);
}
