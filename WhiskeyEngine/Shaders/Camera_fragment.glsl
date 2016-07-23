#version 420 core

layout(location = 0) out vec4 out_color;

in vec4 color;
in vec2 textcoord;

uniform sampler2D gSampler;

void main(){
 
 	//out_color = color;
	out_color = texture2D(gSampler, textcoord.xy);
	//out_color = vec4(textcoord.x,textcoord.y,0,1);
}