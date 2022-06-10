#version 410

struct Material {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform float applyTexture;

uniform Material material;
uniform Light light;  

out vec4 fragColor;

void main(){
   //ambient
   vec3 ambientLight = light.ambient * material.ambient;

   //diffuse
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(light.position - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = light.diffuse * (diff * material.diffuse);
   
   //specular
   //float specularStrength = 0.5;
   vec3 viewDir = normalize(light.position - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = light.specular * (spec * material.specular) * diff;

   
   if (applyTexture > 0.5){
      fragColor = texture(ourTexture, texCoord) * vec4(ambientLight + diffuse + specular, 1.0);
   }
   else{
      vec3 result = ambientLight + diffuse + specular;
      fragColor = vec4(result, 1.0);
   }
}