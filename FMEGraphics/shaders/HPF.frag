#version 330 core

in vec2 TexCoords;
out vec4 color;


uniform vec3 planeColor;
uniform sampler2D Texture0;

void main()
{    
    color = texture(Texture0, TexCoords);	
	
	//vec3 glow = 15.0 * planeColor;
	vec3 glow = color.rgb;
  
	float brightness = dot(glow, vec3(0.2126, 0.7152, 0.0722));
	if(brightness <= 1.0)
	{
	        color = vec4(0.0, 0.0, 0.0, 1.0);    
	}
}



