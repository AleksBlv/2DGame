#version 410

//in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform float applyTexture;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 fragColor;

void main(){
   //ambient
   float ambientStrenght = 0.1f;
   vec3 ambientLight = ambientStrenght * lightColor;

   //diffuese
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightColor;
   

   
   if (applyTexture > 0.5){
      fragColor = texture(ourTexture, texCoord) * vec4(ambientLight + diffuse, 1.0);
   }
   else{
      vec3 result = (ambientLight + diffuse) * objectColor;
      fragColor = vec4(result, 1.0);
   }
}