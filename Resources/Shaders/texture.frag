#version 330 core

in vec2 texCoord;

out vec4 color;

uniform vec4 u_color;
uniform sampler2D u_tex;

void main() 
{
  vec4 texColor = texture(u_tex, texCoord);
  color = texColor * u_color;
}
