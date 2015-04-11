#version 430 core

//input one points each time, but we ouput two points combine a line
layout (points) in;
layout (line_strip, max_vertices = 2) out;

void main() {    
   //point one
    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0); 
    EmitVertex();

	//point two
    gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);
    EmitVertex();
    
	//line
    EndPrimitive();
}    