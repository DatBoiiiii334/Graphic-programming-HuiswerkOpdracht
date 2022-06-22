#version 330 core

layout(location=0) in vec3 vPos;
layout(location=1) in vec3 vNormal; 
layout(location=2) in vec2 vUV;

uniform mat4 world, view, projection;

out vec3 color;
out vec2 uv;
out vec3 normal;
out vec4 worldPixel;

uniform sampler2D heightmap;

void main() {
	worldPixel = world * vec4(vPos, 1.0f);

	vec4 diffuseColor = texture(heightmap, vUV);
	worldPixel.y += diffuseColor.r * 100;

	gl_Position = projection * view * worldPixel;
	uv = vUV;
	normal = mat3(world) * vNormal;
}
