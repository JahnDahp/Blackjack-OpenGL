#version 330 core

in vec2 texCoord;

out vec4 color;

uniform sampler2D u_tex;
uniform vec4 u_color;

void main()
{    
  color = u_color * vec4(1.0, 1.0, 1.0, texture(u_tex, texCoord).r);
} 
