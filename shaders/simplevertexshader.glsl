#version 300 es

in vec3 vertex_pos;
uniform mat4 MVP;

//Notice that the "1" here equals the "1" in glVertexAttribPointer
layout(location = 1) in vec3 vertex_normal;

//The program outputs the fragment colour to the fragment shader
out lowp vec3 fragmentColor;

void main()
{
	//Find the current vertex position from the vertex matrix
	vec4 v = vec4(vertex_pos, 1);

	//Use the MVP matrix to move the vertex position to it's new location
	gl_Position = MVP * v;

	vec3 n = normalize(vertex_normal);
	vec3 cam = normalize(vec3(1.0, 0.3, 1.0));

	fragmentColor = vec3(1.0, 1.0, 1.0) * clamp(dot(n, cam), 0, 1);
	//fragmentColor = vertex_color;
}
