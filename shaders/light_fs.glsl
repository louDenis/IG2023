#version 330 core

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 cameraPos ;

void main()
{
    //ambient
    float ambientStrength = 0.5 ;
    float ambient = lightColor * ambientStrength ;
    
    //diffuse
    vec3 norm = normalize(Normal) ;
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(norm, lightDir), 0.0) ;
    float diffuse = diff * lightColor ;

    //specular
    float specularStrength = 0.5 ;
    vec3 view = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(view, reflectDir), 0.0f), 16);
    float specular = spec * specularStrength *lightColor ;

    vec3 result = (specular + diffuse + ambient) * (Normal * 0.5 + 0.5);
    FragColor = vec4(result, 1.0);
}