#version 410

in vec3 color;
in vec2 texCoord;

uniform sampler2D ourTexture;
uniform int applyTexture;
uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 fragColor;

void main(){
   if (applyTexture == 1.0){
      fragColor = texture(ourTexture, texCoord) * vec4(objectColor * lightColor, 1.0);
   }
   else{
      fragColor = vec4(objectColor * lightColor, 1.0);
   }
}