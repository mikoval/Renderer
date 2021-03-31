#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUv;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 uv_transform;
out vec2 vUv;
void main()
{
   gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
//   vUv = (uv_transform * vec4(aUv, 0.0, 1.0)).xy;
   vUv = aUv;
}

