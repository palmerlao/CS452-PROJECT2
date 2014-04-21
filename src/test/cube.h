vector<GLfloat> cube_normals {
   -ncomp, -ncomp,  ncomp,
    ncomp, -ncomp,  ncomp,
    ncomp,  ncomp,  ncomp, 
   -ncomp,  ncomp,  ncomp,
    ncomp,  ncomp, -ncomp,
   -ncomp,  ncomp, -ncomp,
   -ncomp, -ncomp, -ncomp,
    ncomp, -ncomp, -ncomp
};

vector<GLfloat> cube_texcoords {
  0,1,
  1,1,
  1,0,
  0,0,
};

vector<GLfloat> cube_vertices {
   -1, -1,  1,
    1, -1,  1,
    1,  1,  1, 
   -1,  1,  1,
    1,  1, -1,
   -1,  1, -1,
   -1, -1, -1,
    1, -1, -1 
};

vector<GLfloat> cube_colors {
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f
};
											
vector<GLubyte> cube_elems {
  0, 1, 2,
  0, 2, 3,

  0, 3, 5,
  0, 5, 6,
    
  1, 2, 4,
  1, 4, 7,
		
  2, 3, 4,
  3, 4, 5,
	
  0, 1, 6,
  6, 7, 1,

  5, 6, 7,
  4, 5, 7
};
