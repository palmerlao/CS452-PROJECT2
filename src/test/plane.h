vector<GLfloat> plane_normals {
  -ncomp, -ncomp,
   ncomp, -ncomp,
   ncomp,  ncomp,
  -ncomp,  ncomp
};

vector<GLfloat> plane_texcoords {
  0, 0,
  1, 0,
  1, 1,
 -1, 1
};

vector<GLfloat> plane_vertices {
  -16, -16, -1,
   15, -16, -1,
   15, 15, -1,
  -15, 15, -1
};

vector<GLfloat> plane_colors {
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
};

vector<GLubyte> plane_elems {
  0,1,2,
  2,3,0
};
