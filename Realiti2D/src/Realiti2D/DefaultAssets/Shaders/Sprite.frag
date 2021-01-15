#version 330

in vec2 fragTexCoord;
out vec4 outColor;
uniform sampler2D uTexture;
uniform vec4 uTintColor;

void main() {
	outColor = uTintColor * texture(uTexture, fragTexCoord);
}