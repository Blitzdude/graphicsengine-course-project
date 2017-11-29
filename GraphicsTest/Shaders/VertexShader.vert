#version 100
attribute vec4 vPosition;
attribute vec2 vTexCoord;
uniform mat4 MVP;
varying vec2 texCoord;
void main() 
{
	gl_Position = MVP*vPosition;
	texCoord = vTexCoord;
}