vector<GLfloat> hexprism_vertices {
	//top plane of prism
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, 1.0f,
	0.5f, 0.87f, 1.0f,
	-0.5f, 0.87f, 1.0f,
	0.5f, -0.87f, 1.0f,
	-0.5f, -0.87f, 1.0f,

	//bottom plane of prism
	0.0f, 0.0f, -1.0f,
	1.0f, 0.0f, -1.0f,
	-1.0f, 0.0f, -1.0f,
	0.5f, 0.87f, -1.0f,
	-0.5f, 0.87f, -1.0f,
	0.5f, -0.87f, -1.0f,
	-0.5f, -0.87f, -1.0f,
};

vector<GLfloat> hexprism_tex {
	0,4,
	0,4,
	4,0,
	4,4,
	4,0,
	2,4,
	4,4	
};



vector<GLfloat> hexprism_norms {
	0.0f, 1.0f, 0.0f,
	1/sqrt(2),1/sqrt(2),0,
	-1/sqrt(2),1/sqrt(2),0,
	1/sqrt(11),3/sqrt(11),3/sqrt(11),
	-1/sqrt(11),3/sqrt(11),3/sqrt(11),
	1/sqrt(11),3/sqrt(11),-3/sqrt(11),
	-1/sqrt(11),3/sqrt(11),-3/sqrt(11),
	0.0f, -1.0f, 0.0f,
	1/sqrt(2),-1/sqrt(2),0,
	-1/sqrt(2),-1/sqrt(2),0,
	1/sqrt(11),-3/sqrt(11),3/sqrt(11),
	-1/sqrt(11),-3/sqrt(11),3/sqrt(11),
	1/sqrt(11),-3/sqrt(11),-3/sqrt(11),
	-1/sqrt(11),-3/sqrt(11),-3/sqrt(11)	
};	

vector<GLfloat> hexprism_colors {
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f
};

vector<GLubyte> hexprism_elems {
	//Top hexagonal face
	0, 3, 4,
	0, 1, 3,
	0, 2, 4,
	0, 2, 6,
	0, 5, 6,
	0, 1, 5,

	//Square Face 1
	5, 6, 13,
	5, 12, 13,
	
	//Square Face 2
	1, 5, 12,
	1, 8, 12,
	
	//Square Face 3
	1, 3, 10,
	1, 8, 10,
	
	//Square Face 4
	3, 4, 11,
	3, 10, 11,
	
	//Square Face 5
	4, 2, 9,
	4, 11, 9,

	//Square Face 6
	2, 9, 13,
	2, 6, 13,
	
	//Bottom Hexagonal face
	7, 10, 11,
	7, 8, 10,
	7, 9, 11,
	7, 9, 13,
	7, 12, 13,
	7, 8, 12

};
	
