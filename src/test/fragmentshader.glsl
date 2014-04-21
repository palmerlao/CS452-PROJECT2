#version 130


uniform vec4 Ambient;

uniform vec3 LightColor1;
uniform vec3 LightDirection1;
uniform vec3 HalfVector1;

in vec3 normal;
in vec4 pass_color;
out vec4 out_color;

varying vec2 f_texcoord;
uniform sampler2D texture;

void main()
{
  vec3 amb = vec3(Ambient);
  float diffuse1 = max(0.0, dot(normal, normalize(LightDirection1)));
  float specular1 = max(0.0, dot(normal, normalize(HalfVector1)));
  
  vec3 scatteredLight = Ambient.rgb + LightColor1 * diffuse1;
  vec3 reflectedLight = LightColor1 * specular1 * 20;
 
  if (diffuse1 == 0.0)
      specular1 = 0.0;
  else
      specular1 = pow(specular1, 7);

  vec4 tex = texture2D(texture, f_texcoord);
  vec3 rgb = min( (tex.rgb * amb) * scatteredLight + reflectedLight, vec3(1.0));

//  out_color = vec4(rgb, pass_color.a);
out_color=vec4(tex.rgb,pass_color.a);
}
