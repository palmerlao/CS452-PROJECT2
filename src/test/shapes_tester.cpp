#include "initShaders.h"
#include <cstdlib>
using namespace std;

GLuint program;
GLint uniform_mytexture;
GLint attribute_texcoord;
GLfloat pit,yaw,scalar=1;
glm::vec3 cubeTran;


#include "shape.h"

void rotate(GLuint locate);

GLfloat size=10;

GLfloat ncomp = 1.0f / sqrt(3.0f); // for normal vectors

vector<GLfloat> normsarray {
   ncomp,  ncomp, -ncomp,
   ncomp, -ncomp, -ncomp,
  -ncomp, -ncomp, -ncomp,
  -ncomp,  ncomp, -ncomp,
   ncomp,  ncomp,  ncomp,
   ncomp, -ncomp,  ncomp,
  -ncomp, -ncomp,  ncomp,
  -ncomp,  ncomp,  ncomp
};


vector<GLfloat> cube_texcoords {
  -size, -size,
   size, -size,
   size,  size,
  -size,  size,

  -size, -size,
   size, -size,
   size,  size,
  -size,  size,

  -size, -size,
   size, -size,
   size,  size,
  -size,  size,

  -size, -size,
   size, -size,
   size,  size,
  -size,  size,

  -size, -size,
   size, -size,
   size,  size,
  -size,  size,

  -size, -size,
   size, -size,
   size,  size,
  -size,  size,
};

vector<GLfloat> vertexarray {
	-size, -size, size,
	size, -size, size,
	size, size, size, 
	-size, size, size,
	size, size, -size,
	-size, size, -size,
	-size, -size, -size,
	size, -size, -size
};

vector<GLfloat> colorarray{
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f
};
											
vector<GLubyte> elems {
	0, 1, 2,
	0, 2, 3,
	
	0, 3, 5,
	0, 5, 6,
	
	1, 2, 4,
	1, 4, 7,
		
	2, 3, 4,
	3, 4, 5,
	
	0, 1, 6,
	0, 1, 7,
	
	5, 6, 7,
	4, 5, 7
};

Shape *cube;

void init(){
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  
  glViewport(0, 0, 600, 600);

  ShaderInfo shaders[]={
    { GL_VERTEX_SHADER , "vertexshader.glsl"},
    { GL_FRAGMENT_SHADER , "fragmentshader.glsl"}, 
    { GL_NONE , NULL} 
  };
		
  program=initShaders(shaders);
  
  cube = new Shape(vertexarray, elems, colorarray, normsarray, "texture.png", cube_texcoords);
  
  cube->set_buffers();
  /*  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  attribute_texcoord = glGetAttribLocation(program, "texcoord");
  if (attribute_texcoord == -1)
    fprintf(stderr, "Could not bind attribute %s\n", "texcoord");
  glEnableVertexAttribArray(attribute_texcoord);
  glVertexAttribPointer(attribute_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0); */
}


void display(SDL_Window* screen){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
  /* glm::mat4 trans;
	
  trans=glm::translate(trans,cubeTran);//translate the cube
  trans=glm::rotate(trans,pit,glm::vec3(1,0,0));//rotate the cube around the x axis
  trans=glm::rotate(trans,yaw,glm::vec3(0,1,0));//rotate the cube arround the y axis
  trans=glm::scale(trans,glm::vec3(scalar));//scaling the cube
    
  GLint tempLoc = glGetUniformLocation(program,"modelMatrix");//Matrix that handle the transformations
  glUniformMatrix4fv(tempLoc,1,GL_FALSE,&trans[0][0]);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  uniform_mytexture = glGetUniformLocation(program, "texture");
  glUniform1i(uniform_mytexture, 0); 

  glDrawElements(GL_TRIANGLE_STRIP,36,GL_UNSIGNED_BYTE,NULL); */
  cube->draw();
  
  glFlush();
  SDL_GL_SwapWindow(screen);
}

void input(SDL_Window* screen){

  SDL_Event event;

  while (SDL_PollEvent(&event)){//Handling the keyboard
    switch (event.type){
    case SDL_QUIT:exit(0);break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
      case SDLK_ESCAPE:exit(0);
      case SDLK_w:cubeTran.y+=2;break;
      case SDLK_s:cubeTran.y-=2;break;
      case SDLK_a:cubeTran.x-=2;break;
      case SDLK_d:cubeTran.x+=2;break;
      case SDLK_e:scalar+=.1f;break;
      case SDLK_q:scalar-=.1f;break;
      case SDLK_i:pit+=2;break;
      case SDLK_k:pit-=2;break;
      case SDLK_j:yaw+=2;break;
      case SDLK_l:yaw-=2;break;
      }
    }
  }
}


int main(int argc, char **argv){
	
  //SDL window and context management
  SDL_Window *window;
	
  if(SDL_Init(SDL_INIT_VIDEO)<0){//initilizes the SDL video subsystem
    fprintf(stderr,"Unable to create window: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);//die on error
  }

  //create window
  window = SDL_CreateWindow(
                            "Example", //Window title
                            SDL_WINDOWPOS_UNDEFINED, //initial x position
                            SDL_WINDOWPOS_UNDEFINED, //initial y position
                            500,							//width, in pixels
                            500,							//height, in pixels
                            SDL_WINDOW_OPENGL	//flags to be had
                            );
	
  //check window creation
  if(window==NULL){
    fprintf(stderr,"Unable to create window: %s\n",SDL_GetError());
  }
	

  //creates opengl context associated with the window
  SDL_GLContext glcontext=SDL_GL_CreateContext(window);
	
  //initializes glew
  glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "Unable to initalize GLEW");
    exit(EXIT_FAILURE);
  }
  
  init();
	
  while(true){
    input(window);//keyboard controls
    display(window);//displaying
  }

  SDL_GL_DeleteContext(glcontext);
  SDL_DestroyWindow(window);
  SDL_Quit();
 
  return 0;
}
