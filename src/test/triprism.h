vector<GLfloat> triprism_normals {
  -ncomp, -ncomp,ncomp,
    ncomp, -ncomp, ncomp,
    0, ncomp, ncomp,
    -ncomp, -ncomp, -ncomp,
    ncomp, -ncomp, -ncomp,
    0, ncomp, -ncomp
};

vector<GLfloat> triprism_texcoords {
  0,1,
  0,0,
  1,0,

  0,1,
  0,0,
  1,0,

  0,1,
  0,0,
  1,0,

  0,1,
  1,1,
  1,0,
    
  0,1,
  1,1,
  1,0,

  0,1,
  0,0,
  1,0,

  0,1,
  0,0,
  1,0,

  0,1,
  0,0,
  1,0,
};

vector<GLfloat> triprism_vertices {
  -1, -ncomp, 1,
   1, -ncomp, 1,
   0, 2*ncomp, 1,
  -1, -ncomp, -1,
   1, -ncomp, -1,
   0, 2*ncomp, -1
};

vector<GLfloat> triprism_colors {
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
};

vector<GLubyte> triprism_elems {
  0,1,2,
  3,4,5,

  0,1,4,
  4,3,0,

  1,4,5,
  5,2,1,

  0,3,2,
  2,5,3
};
