/* This line is for Max OSX  */
#include <GLUT/glut.h>
#include <iostream>
using namespace std;
/*! GLUT display callback function */
void display(void);
/*! GLUT window reshape callback function */
void reshape(int, int);
void onMouseClick(int button, int state, int x, int y);

int WIDTH = 1280;
int HEIGHT = 760;
int TOP_OFFSET = 100;
int ENEMY_LEFT_OFFSET = 100;
int USER_LEFT_OFFSET = 600;
int BF_SIZE = 400;
int STEP_SIZE = BF_SIZE/10;
int USER_BATTLE_FIELD[10][10]=
{
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int ENEMY_BATTLE_FIELD[10][10]=
{
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

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

void renderBattleField(int originX, int originY, bool enemyBattleField)
{
  
  glBegin(GL_LINE_LOOP);
    glVertex2f(originX,           originY);
    glVertex2f(BF_SIZE + originX, originY);
    glVertex2f(BF_SIZE + originX, BF_SIZE+originY);
    glVertex2f(originX,           BF_SIZE + originY);
  glEnd();
  
  glBegin(GL_LINES);
    for (int i=0; i<BF_SIZE; i+=STEP_SIZE) {
      glVertex2f(originX,           i+originY         );
      glVertex2f(BF_SIZE + originX, i+originY         );
      glVertex2f(i+originX,         originY           );
      glVertex2f(i+originX,         BF_SIZE + originY );
    }
  glEnd();
  
  int cellCode;
  int leftOffset;
  
  for (int xi=0; xi<BF_SIZE; xi+=STEP_SIZE) {
    for (int yi=0; yi<BF_SIZE; yi+=STEP_SIZE) {
      
      if (enemyBattleField) {
        cellCode = ENEMY_BATTLE_FIELD[yi/STEP_SIZE][xi/STEP_SIZE];
        
        // do not render enemy ships positions
        if (cellCode == 1) {
          continue;
        }
        
        leftOffset = ENEMY_LEFT_OFFSET;
      } else {
        cellCode = USER_BATTLE_FIELD[yi/STEP_SIZE][xi/STEP_SIZE];
        leftOffset = USER_LEFT_OFFSET;
      }
      
      if (cellCode != 0){
        switch (cellCode) {
          case 1:
            glColor3f(0.5, 0.5, 0); break;
          case 2:
            glColor3f(1, 0, 0); break;
        }
        
        int x = xi + leftOffset;
        int y = yi + TOP_OFFSET;
        
        glBegin(GL_POLYGON);
          glVertex2f(x + 10             , y + 10);
          glVertex2f(x + STEP_SIZE - 10 , y + 10);
          glVertex2f(x + STEP_SIZE - 10 , y + STEP_SIZE - 10);
          glVertex2f(x + 10             , y + STEP_SIZE - 10);
        glEnd();
      }
      
    }
  }
}

void onMouseClick(int button, int state, int x, int y)
{
  bool clickedOnEnemy = x < USER_LEFT_OFFSET;
  int leftOffset = clickedOnEnemy ? ENEMY_LEFT_OFFSET : USER_LEFT_OFFSET;
  
  if (button == 0 && state == 1) {
    int xIndex = (x - leftOffset)/STEP_SIZE;
    int yIndex = (y - TOP_OFFSET)/STEP_SIZE;
    
    if (clickedOnEnemy){
      ENEMY_BATTLE_FIELD[yIndex][xIndex] = 2;
    } else {
      USER_BATTLE_FIELD[yIndex][xIndex] = 2;
    }
    
  }
  
  
  glutPostRedisplay();
}

void display()
{
  /* clear the color buffer (resets everything to black) */
  glClear(GL_COLOR_BUFFER_BIT);
  
  glColor3f(1, 0, 0);
  renderBattleField(ENEMY_LEFT_OFFSET, TOP_OFFSET, 1);
  
  glColor3f(1, 1, 1);
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
