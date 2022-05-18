#version 410

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoord;

//out vec3 color;
out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
   //color = vertexColor;
   gl_Position =projection * view * model * vec4(vertexPosition, 1.0);
   FragPos = vec3(model * vec4(vertexPosition, 1.0));
   texCoord = textureCoord;
   Normal = vec3(model * vec4(normal, 1.0));
}