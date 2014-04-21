vector<GLfloat> octo_vertices {
	0.000, 0.000, 1.000,
	1.000, 0.000, 0.000,
	0.000, 1.000, 0.000,
	-1.000, 0.000, 0.000,
	0.000, -1.000, 0.000,
	0.000, 0.000, -1.000
};

vector<GLfloat> octo_norms {
	0.000, 0.000, 1.000,
	1.000, 0.000, 0.000,
	0.000, 1.000, 0.000,
	-1.000, 0.000, 0.000,
	0.000, -1.000, 0.000, 
	0.000, 0.000, -1.000
};


vector<GLfloat> octo_colors {
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f
};


vector<GLfloat> octo_tex {
  0,0,
  0.5,0,
  1,0,
  1,0.5,
  1,1,
  0.5,1,
  0,1,
  0,0.5,
};

vector<GLubyte> octo_elems {
	//top half
	2, 1, 0,
	2, 3, 0,
	2, 1, 5,
	2, 3, 5,
	
	4, 1, 0,
	4, 3, 0,
	4, 1, 5,
	4, 3, 5

};	