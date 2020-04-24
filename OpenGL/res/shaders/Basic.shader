#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vcolor;

out vec3 fcolor;

void main()
{
   gl_Position = position;
   fcolor = vcolor;
};


#shader fragment
#version 330 core

out vec4 color;
in vec3 fcolor;

//uniform vec4 globalColor;

void main()
{
    color = vec4(fcolor, 1.0);
};
