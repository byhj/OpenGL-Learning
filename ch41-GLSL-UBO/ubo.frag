#version 430 core

layout (location = 0) out vec4 fragColor;

uniform int color;

void main()
{
   switch (color) {
      case 0:
	     fragColor = vec4(1.0, 0.0, 0.0, 1.0);
		 break;
	 case 1:
	     fragColor = vec4(0.0, 1.0, 0.0, 1.0);
		 break;
    case 2:
	     fragColor = vec4(0.0, .0, 1.0, 1.0);
		 break;
	 case 3:
	     fragColor = vec4(1.0, 1.0, 0.0, 1.0);
		 break;
	}

}