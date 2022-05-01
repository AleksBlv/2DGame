#version 410

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 textureCoord;

out vec3 color;
out vec2 texCoord;
uniform mat4 transform;

void main(){
   color = vertexColor;
   gl_Position =transform * vec4(vertexPosition, 1.0);
   texCoord = textureCoord;
}