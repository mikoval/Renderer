#version 330 core
out vec4 FragColor;
in vec2 vUv;
uniform vec4 color;
uniform sampler2D image;

void main()
{
   FragColor = texture(image, vUv);
}
