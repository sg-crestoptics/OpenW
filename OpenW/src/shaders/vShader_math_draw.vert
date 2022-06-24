#version 430

in vec2 coord2d;
out vec4 f_color;

void main()
{
	gl_Position = vec4(coord2d.x, coord2d.y, 0, 1);
	f_color = vec4(coord2d.x / 2.0 + 0.5, coord2d.y / 2.0 + 0.5, 1, 1);
}