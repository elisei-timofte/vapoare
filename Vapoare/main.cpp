/* This line is for Max OSX  */
#include <GLUT/glut.h>
#include <iostream>
using namespace std;
/*! GLUT display callback function */
void display(void);
void reshape(int, int);
void onMouseClick(int, int, int, int);

void renderGrid(int, int, bool);
int getLeftOffset(bool);

int WIDTH = 1280;
int HEIGHT = 760;
int TOP_OFFSET = 100;
int ENEMY_LEFT_OFFSET = 100;
int USER_LEFT_OFFSET = 600;
int BF_SIZE = 400;
int STEP_SIZE = BF_SIZE/10;
int USER_BATTLE_FIELD[10][10][2]=
{
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{2,0},{2,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{2,0},{2,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{3,0},{0,0},{0,0},{0,0},{4,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{3,0},{0,0},{0,0},{4,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{3,0},{0,0},{4,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{4,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
};
int ENEMY_BATTLE_FIELD[10][10][2]=
{
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
};
int round = 1;

void renderBattleField(int originX, int originY, bool isEnemyBF)
{
  cout<<"Render Battle field "<<isEnemyBF<<"\n";
  renderGrid(originX, originY, isEnemyBF);
  
  int strikeNo;
  int cellCode;
  int leftOffset = getLeftOffset(isEnemyBF);
  
  for (int xi=0; xi<BF_SIZE; xi+=STEP_SIZE) {
    for (int yi=0; yi<BF_SIZE; yi+=STEP_SIZE) {
      int yIndex = yi/STEP_SIZE;
      int xIndex = xi/STEP_SIZE;
      
      if (isEnemyBF) {
        cellCode = ENEMY_BATTLE_FIELD[yIndex][xIndex][0];
        strikeNo = ENEMY_BATTLE_FIELD[yIndex][xIndex][1];
      } else {
        cellCode = USER_BATTLE_FIELD[yIndex][xIndex][0];
        strikeNo = USER_BATTLE_FIELD[yIndex][xIndex][1];
      }
      // render battle ships
      if (!isEnemyBF and cellCode) {
        switch (cellCode) {
          case 2:
            glColor3f(0.0497, 0.5779, 0.71); break;
          case 3:
            glColor3f(0.1602, 0.5251, 0.89); break;
          case 4:
            glColor3f(0.1152, 0.2701, 0.96); break;
        }
        
        int realX = xIndex * STEP_SIZE + USER_LEFT_OFFSET;
        int realY = yIndex * STEP_SIZE + TOP_OFFSET;
        
        glBegin(GL_POLYGON);
        glVertex2f(realX + 2            , realY + 2);
        glVertex2f(realX + STEP_SIZE - 3 , realY + 2);
        glVertex2f(realX + STEP_SIZE - 3 , realY + STEP_SIZE - 2);
        glVertex2f(realX + 2             , realY + STEP_SIZE - 2);
        glEnd();
      }
      
      // render strikes
      if (strikeNo) {
        glColor3f(1,1,1);
        int realX = xi + leftOffset;
        int realY = yi + TOP_OFFSET;
        
        glBegin(GL_POLYGON);
        glVertex2f(realX + 10             , realY + 10);
        glVertex2f(realX + STEP_SIZE - 10 , realY + 10);
        glVertex2f(realX + STEP_SIZE - 10 , realY + STEP_SIZE - 10);
        glVertex2f(realX + 10             , realY + STEP_SIZE - 10);
        glEnd();
      }
    }
  }
}

void onMouseClick(int button, int state, int x, int y)
{
  bool toogleRender = 0;
  bool clickedOnEnemy = x < (ENEMY_LEFT_OFFSET+BF_SIZE) && x > ENEMY_LEFT_OFFSET && y > TOP_OFFSET && y < (TOP_OFFSET + BF_SIZE);
  bool clickedOnUser = x < (USER_LEFT_OFFSET+BF_SIZE) && x > USER_LEFT_OFFSET && y > TOP_OFFSET && y < (TOP_OFFSET + BF_SIZE);
  int leftOffset = clickedOnEnemy ? ENEMY_LEFT_OFFSET : USER_LEFT_OFFSET;
  
  // left click   && Button_up
  if (button == 0 && state == 1) {
    int xIndex = (x - leftOffset)/STEP_SIZE;
    int yIndex = (y - TOP_OFFSET)/STEP_SIZE;
    
    if (clickedOnEnemy){
      ENEMY_BATTLE_FIELD[yIndex][xIndex][1] = round;
      toogleRender = 1;
    }
    if (clickedOnUser){
      USER_BATTLE_FIELD[yIndex][xIndex][1] = round;
      toogleRender = 1;
    }
    round++;
  }
  
  if (toogleRender) {
    glutPostRedisplay();
  }
  
}

void renderGrid(int originX, int originY, bool isEnemyBattleField)
{
  if (isEnemyBattleField) {
    glColor3f(1, 0, 0);
  } else {
    glColor3f(1, 1, 1);
  }
  
  glBegin(GL_LINE_LOOP);
  glVertex2f(originX,           originY          );
  glVertex2f(originX + BF_SIZE, originY          );
  glVertex2f(originX + BF_SIZE, originY + BF_SIZE);
  glVertex2f(originX,           originY + BF_SIZE);
  glEnd();
  
  glBegin(GL_LINES);
  for (int i=0; i<BF_SIZE; i+=STEP_SIZE) {
    glVertex2f(originX          , originY + i       );
    glVertex2f(originX + BF_SIZE, originY + i       );
    glVertex2f(originX + i      , originY           );
    glVertex2f(originX + i      , originY + BF_SIZE );
  }
  glEnd();
}

int getLeftOffset(bool isEnemyBattleField)
{
  if (isEnemyBattleField) {
    return ENEMY_LEFT_OFFSET;
  } else {
    return USER_LEFT_OFFSET;
  }
}

void display()
{
  /* clear the color buffer (resets everything to black) */
  glClear(GL_COLOR_BUFFER_BIT);
  
  renderBattleField(ENEMY_LEFT_OFFSET, TOP_OFFSET, 1);
  renderBattleField(USER_LEFT_OFFSET, TOP_OFFSET, 0);
  
  /* swap the back and front buffers so we can see what we just drew */
  glutSwapBuffers();
}

/*! glut reshape callback function.  GLUT calls this function whenever
 the window is resized, including the first time it is created.
 You can use variables to keep track the current window size.
 */
void reshape(int width, int height)
{
  /* tell OpenGL we want to display in a recangle that is the
   same size as the window
   */
  glViewport(0,0,width,height);
  
  /* switch to the projection matrix */
  glMatrixMode(GL_PROJECTION);
  
  /* clear the projection matrix */
  glLoadIdentity();
  
  /* set the camera view, orthographic projection in 2D */
  gluOrtho2D(0,width,height,0);
  
  /* switch back to the model view matrix */
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  
  /* set the window size to 512 x 512 */
  glutInitWindowSize(WIDTH, HEIGHT);
  
  /* set the display mode to Red, Green, Blue and Alpha
   allocate a depth buffer
   enable double buffering
   */
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  
  /* create the window (and call it Lab 1) */
  glutCreateWindow("Vapoare");
  
  /* set the glut display callback function
   this is the function GLUT will call every time
   the window needs to be drawn
   */
  
  glutDisplayFunc(display);
  
  glutMouseFunc(onMouseClick);
  
  /* set the glut reshape callback function
   this is the function GLUT will call whenever
   the window is resized, including when it is
   first created
   */
  glutReshapeFunc(reshape);
  
  /* set the default background color to black */
  //  glClearColor(0,0,0,1);
  
  /* enter the main event loop so that GLUT can process
   all of the window event messages
   */
  glutMainLoop();
  
  return 0;
}
