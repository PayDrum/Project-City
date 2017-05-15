#version 430 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Color;
layout (location = 2) in mat4 in_TransformMatrix;
layout (location = 6) in vec3 in_Tilecolor;

uniform mat4 mvpmatrix;

out vec3 ex_Color;

void main(void)
{
	gl_Position = mvpmatrix * in_TransformMatrix * vec4(in_Position, 1.0);
    
	ex_Color = in_Tilecolor;
}
