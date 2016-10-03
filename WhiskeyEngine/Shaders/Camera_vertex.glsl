//It's actually glsl
#version 450 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 in_textcoords;
layout(location = 3) in vec3 in_normal;
 
uniform mat4 projection_matrix, view_matrix, model_matrix;
uniform vec3 rotation;
 
out vec4 color;
out vec2 textcoord;
 
void main()
{
 
    color = in_color;

	mat4 rotate_x, rotate_y, rotate_z;
     
    rotate_x = mat4(1.0, 0.0, 0.0, 0.0,
                    0.0, cos(rotation.x), sin(rotation.x), 0.0,
                    0.0, -sin(rotation.x), cos(rotation.x), 0.0,
                    0.0, 0.0, 0.0, 1.0);
 
    rotate_y = mat4(cos(rotation.y), 0.0, -sin(rotation.y), 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    sin(rotation.y), 0.0, cos(rotation.y), 0.0,
                    0.0, 0.0, 0.0, 1.0);
 
    rotate_z = mat4(cos(rotation.z), -sin(rotation.z), 0.0, 0.0,
                    sin(rotation.z), cos(rotation.z), 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);
 
    //gl_Position = projection_matrix * view_matrix *  rotate_y * rotate_x *rotate_z * vec4(in_position, 1);
	gl_Position = projection_matrix * view_matrix *  model_matrix * vec4(in_position, 1);
	//gl_Position = vec4(in_position, 1) * projection_matrix * view_matrix;
	textcoord = in_textcoords;
     
}