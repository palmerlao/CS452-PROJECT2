#include "initShaders.h"
#include <cstdlib>
using namespace std;

GLuint program;
GLint uniform_mytexture;
GLint attribute_texcoord;

glm::mat4 view;
glm::vec3 cam_loc = glm::vec3(0.0f, -75.0f, 150.0f),
          cam_targ = glm::vec3(0.0f, 0.0f, 0.0f),
          cam_up_dir = glm::vec3(0.0f, 1.0f, 0.0f);

GLfloat size = 10;
GLfloat ncomp = 1.0f / sqrt(3.0f); // for normal vectors
int level_num = 0;

#include "shape.h"
#include "cube.h"
#include "plane.h"
#include "octahedron.h"
#include "hexprism.h"
#include "triprism.h"

#include "game.h"

void rotate(GLuint locate);

Shape *plane;

void draw_board() {
  int x,y;
  plane->bind_buffers();
  plane->draw();
  for (int i=0; i<width; i++) {
    for (int j=0; j<height; j++) {
      if (player_levels[level_num][i][j] != FREE) {
        x = 2*(i-(width/2))*size;
        y = 2*(j-(height/2))*size;
        Shape *tmp;
        switch(player_levels[level_num][i][j]) {
        case A:
          tmp = a;
          break;
        case B:
          tmp = b;
          break;
        case C: tmp = c; break;
        case D:
          tmp = d;
          break;
        case STATIONARY:
          tmp = stationary;
          break;
        case PLAYER:
          tmp = player;
          break;
        }
        tmp->set_trans_x(x);
        tmp->set_trans_y(y);
        tmp->bind_buffers();
        tmp->draw();
      }
    }
  }
}

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
  plane = new Shape(plane_vertices, plane_elems, plane_colors, plane_normals, "t1.jpg", plane_texcoords);

  init_blocks();
  init_grid();
}


void display(SDL_Window* screen){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  view = glm::lookAt(cam_loc, cam_targ, cam_up_dir);
  
  int cnt = 0;
  for (int i=0; i < width; i++)
    for (int j=0; j < height; j++)
      if (player_levels[level_num][i][j] != STATIONARY &&
          player_levels[level_num][i][j] != FREE &&
          player_levels[level_num][i][j] != PLAYER)
        cnt++;
  if (cnt == 0) {
    level_num++;
  }

  if (level_num == levels) {
    cout << "It took you " << moves_made << " moves to complete the game." << endl;
    exit(0);
  }

  draw_board();

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
      case SDLK_i:
        cam_loc.y+=size;
        cam_targ.y+=size;
        break;
      case SDLK_k:
        cam_loc.y-=size;
        cam_targ.y-=size;
        break;
      case SDLK_j:
        cam_loc.x-=size;
        cam_targ.x-=size;
        break;
      case SDLK_l:
        cam_loc.x+=size;
        cam_targ.x+=size;
        break;

      case SDLK_q: break;
      case SDLK_e: break;
      case SDLK_w: move_player(UP); break;
      case SDLK_a: move_player(LEFT); break;
      case SDLK_s: move_player(DOWN); break;
      case SDLK_d: move_player(RIGHT); break;
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
