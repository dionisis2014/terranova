#version 410

//fragment data
in vec3 fragmentColor;
in vec3 fragmentNormal;

//output data
out vec4 fragmentColorOut;

void main() {
	vec3 colorOutput = fragmentColor;
	fragmentColorOut = vec4(colorOutput, 1.0);
}