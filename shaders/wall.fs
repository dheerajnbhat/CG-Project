
#version 130

in vec3 position;

void main()
{
	float modVal = 200.0;
	float vibrancy = 1/modVal;

	if(position.y <= 0)
	{ 
		// water
		gl_FragColor = vec4(0.1, 0.1, 0.75, 1.0);
	} 
	else if(position.y > 0 && position.y <= 5)
	{ 	
		// sand
		gl_FragColor = vec4(0.8, 0.7, 0.5, 1.0);
	} 
	else if(position.y > 5 && position.y <= 10) 
	{ 
		// grass
		gl_FragColor = vec4(0.2, 0.7, 0.2, 1.0);
	} 
	else if(position.y > 10 && position.y <= 15) 
	{ 
		// rocks
		gl_FragColor = vec4(0.4, 0.4, 0.4, 1.0);
	}	
	else if(position.y > 15 && position.y <= 20) 
	{ 
		// black
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}	
	else if(position.y > 20 && position.y <= 25) 
	{ 
		// red
		gl_FragColor = vec4(0.9, 0.0, 0.0, 1.0);
	} 
	else if(position.y > 20 && position.y <= 75) 
	{ 
		// snow
		gl_FragColor = vec4(0.9, 0.9, 0.9, 1.0);
	} 
	else if(position.y > 75 && position.y <= 80) 
	{ 
		// red
		gl_FragColor = vec4(0.9, 0.0, 0.0, 1.0);
	} 
	else if(position.y > 80 && position.y <= 85)
	{ 		
		// black
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	} 
	else if(position.y > 85 && position.y <= 90) 
	{ 
		// rocks
		gl_FragColor = vec4(0.4, 0.4, 0.4, 1.0);
	} 
	else if(position.y > 90 && position.y <= 95) 
	{ 
		// grass
		gl_FragColor = vec4(0.2, 0.7, 0.2, 1.0);		
	}
	else if(position.y > 95 && position.y <= 100) 
	{ 
		// sand
		gl_FragColor = vec4(0.8, 0.7, 0.5, 1.0);	
	
	}	
	else 
	{ 
		// default to black
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
}
