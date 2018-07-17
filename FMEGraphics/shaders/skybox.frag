#version 330 core
out vec4 FragColor;

in vec3 TexCoords;
in vec3 Normal;

uniform samplerCube skybox;


vec4 fisheye()
{
	if(0.0 == Normal.z)
	{
		 vec4 res = texture(skybox, TexCoords);
		 return res;
	}
	vec2 tc;
   tc.s = Normal.z * (TexCoords.s / 2.0 + 0.5);
   tc.t = TexCoords.t / 2.0 + 0.5;
    vec2 thetaphi = ((tc * 2.0) - vec2(1.0)) * vec2(-3.1415926535897932384626433832795 * 0.5, 1.5707963267948966192313216916398);
    vec3 rayDirection = vec3(cos(thetaphi.y) * cos(thetaphi.x), sin(thetaphi.y), cos(thetaphi.y) * sin(thetaphi.x));
    vec4 res = texture(skybox, rayDirection);
	return res;
}



void main()
{    
  
 // FragColor = fisheye();
  FragColor = texture(skybox, TexCoords);
}