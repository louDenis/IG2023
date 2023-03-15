#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;
  
uniform vec3 lightPos; 
uniform vec3 cameraPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform float linear ;
uniform float constant ;
uniform float quadratic ;

// texture sampler
uniform sampler2D texture1;

float norme(float x, float y, float z) {
    return sqrt(x*x + y*y + z*z);
}

void main()
{
    float x = lightPos.x - FragPos.x ;
    float y = lightPos.y - FragPos.y ;
    float z = lightPos.z - FragPos.z ;
    
    float distance    =  length(normalize(lightPos) - normalize(FragPos));
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));       

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    if (diff == 0.0)
    {
    	norm = -norm ;
    	diff = max(dot(norm, lightDir), 0.0);
    	
    }
    vec3 diffuse = diff * lightColor;
    
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor; 
    
 
    float n = norme(x, y, z); 
    
    specular *= attenuation;
    ambient *= attenuation ;
    diffuse *= attenuation ;
        
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = texture(texture1, TexCoords) * vec4(result, 1.0);
} 
