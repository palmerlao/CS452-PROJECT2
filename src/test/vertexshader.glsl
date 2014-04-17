#version 130

uniform mat4 Matrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

attribute vec2 texcoord;
varying vec2 f_texcoord;

in vec3 in_position;

in vec4 in_color;
in vec3 in_normal;

out vec4 pass_color;
out vec3 normal;

void main(){
  gl_Position=Matrix*viewMatrix*modelMatrix*vec4(in_position,1.0);
  normal = in_normal;
  f_texcoord = texcoord;
  pass_color=in_color;
}
