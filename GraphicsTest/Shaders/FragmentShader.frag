precision mediump float;
varying vec2 texCoord;
void main() 
{
	gl_FragColor = 0.5*(texCoord.y+texCoord.x) * vec4 (1.0,1.0,1.0,1.0);
}