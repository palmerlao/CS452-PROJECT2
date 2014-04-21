#version 130

uniform mat4 Matrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform vec4 Ambient;
uniform vec3 LightColor1;
uniform vec3 LightDirection1;
uniform vec3 HalfVector1;

attribute vec2 texcoord;
varying vec2 f_texcoord;

in vec3 in_position;

in vec4 in_color;
in vec3 in_normal;

out vec4 pass_color;
out vec3 normal;

out vec4 Amb;
out vec3 LightCol1;
out vec3 LightDir1;
out vec3 HalfVec1;

void main(){
  gl_Position=Matrix*viewMatrix*modelMatrix*vec4(in_position,1.0);
  normal = in_normal;
  f_texcoord = texcoord;
  pass_color=in_color;

  Amb = Ambient;
  LightCol1 = LightColor1;
  LightDir1 = (Matrix*viewMatrix*modelMatrix*vec4(LightDirection1,1.0)).xyz;
  HalfVec1 = (Matrix*viewMatrix*modelMatrix*vec4(HalfVector1,1.0)).xyz;
}
