#version 410

//vertex data
in vec3 vertexPosition;
in vec2 vertexUv;
in vec3 vertexNormal;

//fragment data
out vec2 fragmentUv;
out vec3 fragmentNormal;

//uniforms
uniform mat4 matrixPV;
uniform mat4 matrixM;

void main() {
	//passthrough
	fragmentUv = vertexUv;
	fragmentNormal = vertexNormal;

	gl_Position = matrixPV * matrixM * vec4(vertexPosition, 1.0);
}