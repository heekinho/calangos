//GLSL
#version 140
#extension GL_ARB_compatibility : enable
//#extension GL_EXT_gpu_shader4 : enable 

//const int num_instances = 128;
//uniform vec4 shader_data[num_instances * 4];
//uniform sampler2D p3d_Texture0;


uniform mat4 p3d_ModelViewProjectionMatrix;
in vec4 p3d_Vertex;
in vec4 p3d_MultiTexCoord0;

uniform sampler2D transforms_tex;
uniform vec2 transforms_tex_size;
uniform int instance_tex_offset;

void main() {
  vec2 size = transforms_tex_size;
  
  // More legible  
  float dcol = (1.0 / size.x);
  float drow = (1.0 / size.y);
  
  int id = (gl_InstanceID + instance_tex_offset) * 4;
  
  float col = int(mod(id, size.x)) * dcol + (0.5*dcol);
  float row = int(id / size.x) * drow + (0.5*drow);
  
  vec4 col0 = texture(transforms_tex, vec2(col + 0*dcol, row));
  vec4 col1 = texture(transforms_tex, vec2(col + 1*dcol, row));
  vec4 col2 = texture(transforms_tex, vec2(col + 2*dcol, row));
  vec4 col3 = texture(transforms_tex, vec2(col + 3*dcol, row));
  
  mat4 transform = mat4(col0.zyxw, col1.zyxw, col2.zyxw, col3.zyxw);
  
  gl_Position = p3d_ModelViewProjectionMatrix * (p3d_Vertex * transform);
  gl_TexCoord[0] = p3d_MultiTexCoord0;
  //gl_FrontColor = gl_Color;

}