#version 330 core

layout (location = 0) in vec4 iVertex;

out vec2 oTextCoords;

uniform mat4 projection;

void main()
{
  gl_Position = projection * vec4(iVertex.xy, 0.0, 1.0);
  oTextCoords = iVertex.zw;
}
