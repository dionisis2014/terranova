#version 410

//vertex data
in vec3 vertexPosition;
in vec3 vertexColor;
in vec3 vertexNormal;

//fragment data
out vec3 fragmentColor;
out vec3 fragmentNormal;

//uniforms
uniform mat4 matrixPV;
uniform mat4 matrixM;

void main() {
	//passthrough
	fragmentColor = vertexColor;
	fragmentNormal = vertexNormal;

	gl_Position = matrixPV * matrixM * vec4(vertexPosition, 1.0);
}