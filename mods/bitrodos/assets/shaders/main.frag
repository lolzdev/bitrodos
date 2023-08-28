#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2DArray tex;
  
void main()
{
    FragColor = texture(tex, vec3(TexCoord.xy, 0));
}
