#version 410

struct Material {
   sampler2D diffuse;
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
uniform vec3 cameraPos;
uniform Material material;
uniform Light light;  

out vec4 fragColor;

void main(){
   //ambient
   vec3 ambientLight = light.ambient * vec3(texture(material.diffuse, texCoord));

   //diffuse
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(light.position - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
   
   //specular
   vec3 viewDir = normalize(cameraPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = light.specular * (spec * material.specular);

   
   
   vec3 result = ambientLight + diffuse + specular;
   fragColor = vec4(result, 1.0);
}