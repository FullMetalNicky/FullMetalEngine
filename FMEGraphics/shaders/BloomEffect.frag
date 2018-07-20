#version 330 core
out vec4 FragColor;


in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;


void main()
{	
	FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);	
  	float exposure = 1.0f;
  	const float gamma = 2.2;
  	vec3 result; 
  	
    vec3 hdrColor = texture(texture0, TexCoord).rgb;  
    vec3 bloomColor = texture(texture1, TexCoord).rgb;   	
  	result = hdrColor + bloomColor;

//	result = vec3(1.0) - exp(-result * 0.1);
    result = pow(result, vec3(1.0 / gamma));
 
    FragColor = vec4(result, 1.0);
} 