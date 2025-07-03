#version 330 core

layout(location = 0) in vec4 vertex;

out vec2 texCoord;

uniform mat4 u_proj;

void main()
{
  gl_Position = u_proj * vec4(vertex.xy, 0.0, 1.0);
  texCoord = vertex.zw;
}  
