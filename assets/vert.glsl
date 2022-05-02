#version 410

layout(location = 0) in vec3 vertexPosition;
layout(location = 2) in vec3 vertexColor;
layout(location = 1) in vec2 textureCoord;

out vec3 color;
out vec2 texCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
   color = vertexColor;
   gl_Position =projection * view * model * vec4(vertexPosition, 1.0);
   texCoord = textureCoord;
}