#version 460 core
layout (location = 0) in int aPos;  

out vec2 TexCoord;

uniform mat4 perspective;
uniform mat4 view;

vec2 calculate_uvs(int v)
{
    int index = v & 0xff;
    int y = (index/16) * 16;
    int x = (index%16) * 16;

    switch(gl_VertexID % 4) {
        case 0:
            return vec2((float(x) + 16.0) / 256.0, float(y) / 256.0);
        case 1:
            return vec2((float(x) + 16.0) / 256.0, (float(y) + 16.0) / 256.0);
        case 2:
            return vec2(float(x) / 256.0, (float(y) + 16.0) / 256.0);
        case 3:
            return vec2(float(x) / 256.0, float(y) / 256.0);
        default:
            return vec2(0, 0);
    }
}

vec3 decode_vertex(int v)
{
    return vec3(((v >> 28) & 0xf), ((v >> 16) & 0xff), ((v >> 24) & 0xf));
}

void main()
{
    gl_Position = perspective * view * vec4(decode_vertex(aPos), 1.0);
    TexCoord = calculate_uvs(aPos);
}
