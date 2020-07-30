#version 410

//fragment data
in vec3 fragmentColor;
in vec3 fragmentNormal;

//output color
out vec4 fragmentColorOut;

void main() {
	fragmentColorOut = vec4(fragmentColor, 1.0);
}