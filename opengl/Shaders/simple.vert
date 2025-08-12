
#version 460 core
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vColor;

out vec3 color;
uniform mat4 transform;

void main() {
  color = vColor;
  gl_Position =  transform * vec4(vertex_position, 1.0);
}
