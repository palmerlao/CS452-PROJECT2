#include <string>
#include <vector>
#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SOIL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shape{
  GLuint vaoID, vboID[3], eboID, textureID, texcoordsID;
  GLfloat *vertices, *colors, *normals, *tex_coords;
  GLubyte *elements;
  GLfloat pit=0, yaw=0, scale=size;
  glm::vec3 translate_vec;
  int vsz, esz, csz, nsz, tsz;
  unsigned char *img;
  int img_width, img_height;
  
 public:
  Shape(vector<GLfloat> vs,
        vector<GLubyte> es,
        vector<GLfloat> cs,
        vector<GLfloat> ns,
        string texture_img,
        vector<GLfloat> tcs);
  ~Shape();
  void bind_buffers();
  void draw();

  void set_pit(GLfloat p) { pit = p; }
  void set_yaw(GLfloat y) { yaw = y; }
  void set_scale(GLfloat s) { scale = s; }
  void set_trans_x(GLfloat x) { translate_vec.x = x; }
  void set_trans_y(GLfloat y) { translate_vec.y = y; }
  void set_trans_z(GLfloat z) { translate_vec.z = z; }

  void add_pit(GLfloat p) { pit += p; }
  void add_yaw(GLfloat y) { yaw += y; }
  void add_scale(GLfloat s) { scale += s; }
  void add_trans_x(GLfloat x) { translate_vec.x += x; }
  void add_trans_y(GLfloat y) { translate_vec.y += y; }
  void add_trans_z(GLfloat z) { translate_vec.z += z; }

 private:
  template <typename T>
  T* vector_to_array( vector<T> vec ) {
    T* ret = new T[vec.size()];
    for (unsigned i=0; i<vec.size(); i++)
      ret[i] = vec[i];
    return ret;
  }
};


Shape::Shape(vector<GLfloat> vs,
             vector<GLubyte> es,
             vector<GLfloat> cs,
             vector<GLfloat> ns,
             string texture_img,
             vector<GLfloat> tcs) {

  vsz = vs.size();
  vertices = vector_to_array(vs);
  esz = es.size();
  elements = vector_to_array(es);

  csz = cs.size();
  colors = vector_to_array(cs);

  nsz = ns.size();
  normals = vector_to_array(ns);

  tsz = tcs.size();
  tex_coords = vector_to_array(tcs);
  img = SOIL_load_image(texture_img.c_str(), &img_width, &img_height, NULL, 0);

  /*Generate Appropriate Buffers*/
  glGenVertexArrays(1,&vaoID); 
  glGenBuffers(3,vboID);

  glGenBuffers(1,&eboID);

  glGenBuffers(1,&texcoordsID);

  glGenTextures(1,&textureID);
}

Shape::~Shape() {
  delete[] vertices;
  delete[] colors;
  delete[] normals;
  delete[] tex_coords;
  delete[] elements;
  delete[] img;
}

void Shape::bind_buffers() {
  glBindVertexArray(vaoID);

  glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
  glBufferData(GL_ARRAY_BUFFER, vsz*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, esz*sizeof(GLubyte), elements, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
  glBufferData(GL_ARRAY_BUFFER, csz*sizeof(GLfloat), colors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
  glBufferData(GL_ARRAY_BUFFER, nsz*sizeof(GLfloat), normals, GL_STATIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, texcoordsID);
  glBufferData(GL_ARRAY_BUFFER, tsz*sizeof(GLfloat), tex_coords, GL_STATIC_DRAW);

  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, //target
               0, //level, 0=base, no minimap
               GL_RGB, //internal format
               img_width,
               img_height,
               0, //border, always 0 in opengl es
               GL_RGB,
               GL_UNSIGNED_BYTE, //type
               img);

 glEnableVertexAttribArray(0);
 glEnableVertexAttribArray(1);
 glEnableVertexAttribArray(2);

 attribute_texcoord = glGetAttribLocation(program, "texcoord");
 if (attribute_texcoord == -1)
    fprintf(stderr, "Could not bind texcoord attribute\n");
 glEnableVertexAttribArray(attribute_texcoord);
 glVertexAttribPointer(attribute_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void Shape::draw() {
  glm::mat4 trans;
  trans=glm::translate(trans,translate_vec);
  trans=glm::rotate(trans,pit,glm::vec3(1.0f,0.0f,0.0f));
  trans=glm::rotate(trans,yaw,glm::vec3(0.0f,1.0f,0.0f));
  trans=glm::scale(trans,glm::vec3(scale));
    
  GLint tempLoc = glGetUniformLocation(program,"modelMatrix");//Matrix that handle the transformations
  glUniformMatrix4fv(tempLoc,1,GL_FALSE,&trans[0][0]);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureID);
  uniform_mytexture = glGetUniformLocation(program, "texture");
  glUniform1i(uniform_mytexture, 0);

  GLfloat ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};
  GLfloat light1_dir[] = {40.0f, 40.0f, 40.0f};
  GLfloat light1_color[] = {0.1f, 0.1f, 0.1f};

  tempLoc = glGetUniformLocation(program,"Ambient");
  glUniform4fv(tempLoc,1,ambient);
  tempLoc = glGetUniformLocation(program,"LightColor1");
  glUniform3fv(tempLoc,1,light1_color);
  tempLoc = glGetUniformLocation(program,"LightDirection1");
  glUniform3fv(tempLoc,1,light1_dir);
  tempLoc = glGetUniformLocation(program,"HalfVector1");
  glUniform3fv(tempLoc,1,light1_dir);

  glDrawElements(GL_TRIANGLES, esz, GL_UNSIGNED_BYTE, NULL);
}
