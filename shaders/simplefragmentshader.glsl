#version 300 es
out lowp vec3 color;

in lowp vec3 fragmentColor;

void main()
{
	color = fragmentColor;
}
