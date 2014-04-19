#include "initShaders.h"
#include <cstdlib>
using namespace std;

GLuint program;
GLint uniform_mytexture;
GLint attribute_texcoord;

GLfloat size = 10;
GLfloat ncomp = 1.0f / sqrt(3.0f); // for normal vectors

#include "shape.h"
#include "cube.h"
#include "triprism.h"
#include "plane.h"

void rotate(GLuint locate);

vector<Shape*> shapes;

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
  shapes.push_back(new Shape(plane_vertices, plane_elems, plane_colors, plane_normals, "t1.png", plane_texcoords));
  shapes[0]->set_scale(size*10);
  shapes[0]->set_trans_y(-50);
  //  shapes.push_back(new Shape(triprism_vertices, triprism_elems, triprism_colors, triprism_normals, "t3.jpg", triprism_texcoords));
}


void display(SDL_Window* screen){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  for (unsigned i=0; i < shapes.size(); i++) {
    shapes[i]->bind_buffers();
    shapes[i]->draw();
  }
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
      case SDLK_w: shapes[0]->add_trans_y(2); break;
      case SDLK_s: shapes[0]->add_trans_y(-2); break;
      case SDLK_a: shapes[0]->add_trans_x(-2); break;
      case SDLK_d: shapes[0]->add_trans_x(2); break;
      case SDLK_e: shapes[0]->add_scale(-.1f); break;
      case SDLK_q: shapes[0]->add_scale(.1f); break;
      case SDLK_i: shapes[0]->add_pit(2); break;
      case SDLK_k: shapes[0]->add_pit(-2); break;
      case SDLK_j: shapes[0]->add_yaw(2); break;
      case SDLK_l: shapes[0]->add_yaw(-2); break;
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
