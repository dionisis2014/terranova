#version 410

//fragment data
in vec2 fragmentUv;
in vec3 fragmentNormal;

//output data
out vec4 fragmentColorOut;

//uniforms
uniform sampler2D fragmentTexture;

void main() {
	vec4 textureColor = texture(fragmentTexture, fragmentUv);
	fragmentColorOut = mix(textureColor, vec4(1.0,1.0,1.0,1.0), 0.5);
}