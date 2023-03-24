#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

// Inspired by the following link, rewrote diffuse and specular lighting into different functions for clarity
// https://learnopengl.com/code_viewer.php?code=lighting/basic_lighting-exercise2

vec3 Diffuse(){
  vec3 norm = normalize(Normal); 
	vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  return diff * lightColor;
}

vec3 Specular(){
  vec3 lightDir = normalize(lightPos - FragPos);
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	return (0.5 * spec * lightColor); // 0.5 is specular strength
}

void main(){
  vec3 ambient  = (0.1 * lightColor) * objectColor; // 0.1 is ambient strength

	vec3 diffuse  = Diffuse();
	vec3 specular = Specular();

	vec3 result = (ambient + diffuse + specular) * objectColor;
	color = vec4(result, 1.0);
} 
