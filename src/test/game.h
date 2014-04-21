enum block_t {FREE, STATIONARY, A, B, C, D, PLAYER};
enum move_t {UP, DOWN, LEFT, RIGHT};
const int levels = 3, width = 16, height = 16;

block_t level[levels][width][height];
block_t player_levels[levels][width][height];

Shape *a, *b, *c, *d, *player, *stationary;

void init_grid(){
  int i, j, k;
  for(i = 0; i < levels; i++) {
    for(j = 0; j < width; j++)
      for(k = 0; k < height; k++)
        level[i][j][k] = FREE;
    for(j = 0; j < height; j++) {
      level[i][0][j] = STATIONARY;
      level[i][width-1][j] = STATIONARY;
    }
    for(j=0; j < width; j++) {
      level[i][j][height-1] = STATIONARY;
      level[i][j][0] = STATIONARY;
    }
  }
  for (i=0; i<levels; i++) {
    level[i][1][6] = A;
    level[i][1][7] = A;
    level[i][2][6] = B;
    level[i][3][6] = C;
    level[i][2][5] = D;
    level[i][2][4] = A;
    level[i][7][5] = A;
    level[i][3][3] = B;
    level[i][3][4] = C;
    level[i][2][7] = D;
    level[i][4][4] = PLAYER;
  }
  memcpy(&player_levels, &level, levels*width*height*sizeof(block_t));
}

void init_blocks() {
  a = new Shape(triprism_vertices, triprism_elems, triprism_colors, triprism_normals, "t2.jpg", triprism_texcoords);
  b = new Shape(cube_vertices, cube_elems, cube_colors, cube_normals, "t3.jpg", cube_texcoords);
  c = new Shape(triprism_vertices, triprism_elems, triprism_colors, triprism_normals, "t4.jpg", triprism_texcoords);
  d = new Shape(cube_vertices, cube_elems, cube_colors, cube_normals, "t5.jpg", cube_texcoords);
  player = new Shape(cube_vertices, cube_elems, cube_colors, cube_normals, "player.jpg", cube_texcoords);
  fprintf(stderr, "blocks initialized\n");
  fprintf(stderr, "a's address: %p\n",a);
}

bool is_in_bounds(int x, int y) {
  if (x > 0 && x < width && y > 0 && y < height) {
    return true;
  }
  return false;
}

bool is_valid_move(int x, int y, move_t mvt) {
  block_t fst, snd;
  int nx, ny;
  if (!is_in_bounds(x,y)) {
    return false;
  } else if (player_levels[level_num][x][y] == FREE) {
    return true;
  } else if (player_levels[level_num][x][y] == STATIONARY) {
    return false;
  } else { // block checks
    fst = player_levels[level_num][x][y];
    switch (mvt) {
    case UP:
      if (is_in_bounds(x,y+1)) {
        snd = player_levels[level_num][x][y+1];
        nx = x; ny = y+1;
      }
      break;
    case LEFT:
      if (is_in_bounds(x-1, y)) {
        snd = player_levels[level_num][x-1][y];
        nx = x-1; ny = y;
      } else {
        return false;
      }
      break;
    case RIGHT:
      if (is_in_bounds(x+1,y)) {
        snd = player_levels[level_num][x+1][y];
        nx = x+1; ny = y;
      }
      break;
    case DOWN:
      if (is_in_bounds(x,y-1)) {
        snd = player_levels[level_num][x][y-1];
        nx = x; ny = y-1;
      } else {
        return false;
      }
      break;
    default:
      snd = STATIONARY;
      return false;
      break;
    }
    if (fst == snd) {
      player_levels[level_num][nx][ny] = FREE;
      return true;
    } else if (snd == FREE) {
      player_levels[level_num][nx][ny] = fst;
      return true;
    } else {
      return false;
    }
  }
  cout << "fuck\n" << endl;
  return false;
}

void move_player(move_t mvmt) {
  int i, j, k, l;
  int new_coordx, new_coordy;
  for (k=0; k<width; k++) {
    for (l=0; l<height; l++) {
      if (player_levels[level_num][k][l] == PLAYER) {
        i=k; j=l;
      }
    }
  }
  switch (mvmt) {
  case UP:
    new_coordx = i;
    new_coordy = j+1;
    break;
  case LEFT:
    new_coordx = i-1;
    new_coordy = j;
    break;
  case RIGHT:
    new_coordx = i+1;
    new_coordy = j;
    break;
  case DOWN:
    new_coordx = i;
    new_coordy = j-1;
    break;
  default:
    cout << "bad movement\n";
  }
  if (is_valid_move(new_coordx, new_coordy, mvmt)) {
    player_levels[level_num][i][j] = FREE;
    player_levels[level_num][new_coordx][new_coordy] = PLAYER;
  }
}
