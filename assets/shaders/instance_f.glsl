//GLSL
#version 140
#extension GL_ARB_compatibility : enable

uniform sampler2D p3d_Texture0;
//uniform sampler2D p3d_Texture1;

uniform sampler2D transforms_tex;

void main() {
  gl_FragColor = texture(p3d_Texture0, vec2(gl_TexCoord[0]));
}