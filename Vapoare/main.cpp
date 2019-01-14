/* This line is for Max OSX  */
#include <GLUT/glut.h>
#include <iostream>
using namespace std;
/*! GLUT display callback function */
void display(void);
void reshape(int, int);
void onMouseClick(int, int, int, int);

void renderGrid(int, int, bool);
void onBattleFieldClick(int, int, int, int);
void setColorByCellCode(int);
void renderButtons();
void renderResetButton();
void renderClearButton();
void renderSubmitButton();
void renderButton(int);
void onButtonsClick(int, int, int, int);
int getLeftOffset(bool);

int WIDTH = 1280;
int HEIGHT = 760;

int TOP_OFFSET = 100;
int ENEMY_LEFT_OFFSET = 600;
int USER_LEFT_OFFSET = 100;

int BF_SIZE = 400;
int SHC_OFFSET = 50;
int STEP_SIZE = BF_SIZE/10;

int BUTTON_HEIGHT = 70;
int BUTTON_TOP_OFFSET = TOP_OFFSET + BF_SIZE + 100;
int BUTTON_WIDTH = 150;
int CLEAR_BUTTON_OFFSET = 650;
int SUBMIT_BUTTON_OFFSET = 850;

int cannonFires = 0;
int ENEMY_SHIPS[4];
int USER_BATTLE_FIELD[10][10][2]=
{
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{1,0},{1,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
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
  {{0,0},{1,0},{1,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{4,0},{4,0},{4,0},{4,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{3,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{0,0},{0,0},{0,0},{3,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
  {{0,0},{2,0},{2,0},{3,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
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
//      if (cellCode) {
        setColorByCellCode(cellCode);
        
        int realX = xIndex * STEP_SIZE + USER_LEFT_OFFSET;
//        int realX = xIndex * STEP_SIZE + leftOffset;
        int realY = yIndex * STEP_SIZE + TOP_OFFSET;
        
        glBegin(GL_POLYGON);
          glVertex2f(realX + 2             , realY + 2);
          glVertex2f(realX + STEP_SIZE - 3 , realY + 2);
          glVertex2f(realX + STEP_SIZE - 3 , realY + STEP_SIZE - 2);
          glVertex2f(realX + 2             , realY + STEP_SIZE - 2);
        glEnd();
      }
      
      // render strikes
      if (strikeNo) {
        if (strikeNo > 0) {
          if (cellCode) {
            glColor3f(1,0,0); //red
          } else {
            glColor3f(1,1,1); //white
          }
        } else if (strikeNo == -1) {
          glColor3f(0.68,0.5984,0.5984); //gray
        }
        
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
  // render enemy ships hits column
  if (isEnemyBF) {
    int columnX = ENEMY_LEFT_OFFSET + BF_SIZE + SHC_OFFSET;
    int columnY;
    
    if (ENEMY_SHIPS[1] || ENEMY_SHIPS[2] || ENEMY_SHIPS[3] || ENEMY_SHIPS[4]) {
      for (int i=1; i<=4; i++) {
        switch (i) {
          case 1:
            columnY = TOP_OFFSET + BF_SIZE - STEP_SIZE; break;
          case 2:
            columnY = TOP_OFFSET + BF_SIZE - 3*STEP_SIZE; break;
          case 3:
            columnY = TOP_OFFSET + BF_SIZE - 5*STEP_SIZE; break;
          case 4:
            columnY = TOP_OFFSET + BF_SIZE - 8*STEP_SIZE; break;
        }
        
        for (int j=0; j<ENEMY_SHIPS[i]; j++) {
          int tempColumnY = columnY - j * STEP_SIZE;
          
          setColorByCellCode(i);
          
          glBegin(GL_POLYGON);
          glVertex2f(columnX + 3             , tempColumnY + 4);
          glVertex2f(columnX + STEP_SIZE - 5 , tempColumnY + 4);
          glVertex2f(columnX + STEP_SIZE - 5 , tempColumnY + STEP_SIZE - 3);
          glVertex2f(columnX + 3             , tempColumnY + STEP_SIZE - 3);
          glEnd();
        }
      }
    }
  }
}

void onMouseClick(int button, int state, int x, int y)
{
  onBattleFieldClick(button, state, x, y);
  onButtonsClick(button, state, x , y);
  
}

void renderGrid(int originX, int originY, bool isEnemyBF)
{
  if (isEnemyBF) {
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
  for (int i=STEP_SIZE; i<BF_SIZE; i+=STEP_SIZE) {
    glVertex2f(originX          , originY + i       );
    glVertex2f(originX + BF_SIZE, originY + i       );
    glVertex2f(originX + i      , originY           );
    glVertex2f(originX + i      , originY + BF_SIZE );
    
    if (isEnemyBF) {
      int yi = i/STEP_SIZE;
      if (yi == 3 || yi == 6 || yi == 8){
        glVertex2f(originX + BF_SIZE + SHC_OFFSET             , originY + i );
        glVertex2f(originX + BF_SIZE + SHC_OFFSET + STEP_SIZE , originY + i );
      }
    }
  }
  glEnd();
  
  //  render ships hits column
  if (isEnemyBF) {
    glBegin(GL_LINE_LOOP);
      glVertex2f(originX + BF_SIZE + SHC_OFFSET             , originY - STEP_SIZE );
      glVertex2f(originX + BF_SIZE + SHC_OFFSET + STEP_SIZE , originY - STEP_SIZE );
      glVertex2f(originX + BF_SIZE + SHC_OFFSET + STEP_SIZE , originY + BF_SIZE   );
      glVertex2f(originX + BF_SIZE + SHC_OFFSET             , originY + BF_SIZE   );
    glEnd();
  }
}

int getLeftOffset(bool isEnemyBattleField)
{
  if (isEnemyBattleField) {
    return ENEMY_LEFT_OFFSET;
  } else {
    return USER_LEFT_OFFSET;
  }
}

void setColorByCellCode(int cellCode)
{
  switch (cellCode) {
    case 1:
      glColor3f(0.67, 0.3779, 0.91); break;
    case 2:
      glColor3f(0.0497, 0.5779, 0.71); break;
    case 3:
      glColor3f(0.3276, 0.8906, 0.91); break;
    case 4:
      glColor3f(0.1152, 0.2701, 0.96); break;
  }
}

void renderButtons()
{
  renderResetButton();
  renderClearButton();
  renderSubmitButton();
}

void renderResetButton()
{
  glColor3f(1, 0, 0);
  
  renderButton(USER_LEFT_OFFSET);
}

void renderClearButton()
{
  glColor3f(1, 0.8167, 0);
  
  renderButton(CLEAR_BUTTON_OFFSET);
}

void renderSubmitButton()
{
  glColor3f(0.0846, 0.63, 0.0126);
  
  renderButton(SUBMIT_BUTTON_OFFSET);
}

void renderButton(int leftOffset)
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
  glBegin(GL_QUADS);
    glVertex2f(leftOffset, BUTTON_TOP_OFFSET);
    glVertex2f(leftOffset + BUTTON_WIDTH, BUTTON_TOP_OFFSET);
    glVertex2f(leftOffset + BUTTON_WIDTH, BUTTON_TOP_OFFSET + BUTTON_HEIGHT);
    glVertex2f(leftOffset, BUTTON_TOP_OFFSET + BUTTON_HEIGHT);
  glEnd();
}

void onButtonsClick(int button, int state, int x, int y)
{
  bool toogleRender = 0;
  bool clickedOnReset = x < (USER_LEFT_OFFSET+BUTTON_WIDTH) && x > USER_LEFT_OFFSET && y > BUTTON_TOP_OFFSET && y < (BUTTON_TOP_OFFSET + BUTTON_HEIGHT);
  bool clickedOnClear = x < (CLEAR_BUTTON_OFFSET+BUTTON_WIDTH) && x > CLEAR_BUTTON_OFFSET && y > BUTTON_TOP_OFFSET && y < (BUTTON_TOP_OFFSET + BUTTON_HEIGHT);
  bool clickedOnSubmit = x < (SUBMIT_BUTTON_OFFSET+BUTTON_WIDTH) && x > SUBMIT_BUTTON_OFFSET && y > BUTTON_TOP_OFFSET && y < (BUTTON_TOP_OFFSET + BUTTON_HEIGHT);
  
  if (clickedOnReset) {
    for (int i=0; i<=4; i++ ){
        ENEMY_SHIPS[i] = 0;
    }
    
    for (int i=0; i<10; i++) {
      for (int j=0; j<10; j++) {
        ENEMY_BATTLE_FIELD[i][j][1] = 0;
        USER_BATTLE_FIELD[i][j][1] = 0;
      }
    }
    round = 1;
    toogleRender = 1;
  }
  
  if (clickedOnSubmit) {
    for (int i=0; i<10; i++) {
      for (int j=0; j<10; j++) {
        int strikeNo = ENEMY_BATTLE_FIELD[i][j][1];
        
        if (strikeNo == -1) {
          // mark as shooted
          ENEMY_BATTLE_FIELD[i][j][1] = round;
          
          int shipLenth = ENEMY_BATTLE_FIELD[i][j][0];
          
          if (shipLenth && ENEMY_SHIPS[shipLenth] <= shipLenth) {
            ENEMY_SHIPS[shipLenth]++;
          }
        }

      }
    }
    round++;
    cannonFires = 0;
    toogleRender = 1;
  }
  
  if (toogleRender) {
    glutPostRedisplay();
  }
}

void onBattleFieldClick(int button, int state, int x, int y)
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
      if (!ENEMY_BATTLE_FIELD[yIndex][xIndex][1] and cannonFires <=7) {
        ENEMY_BATTLE_FIELD[yIndex][xIndex][1] = -1;
        cannonFires++;
        
        toogleRender = 1;
      }
    }
    if (clickedOnUser){
      USER_BATTLE_FIELD[yIndex][xIndex][1] = round;
      toogleRender = 1;
    }
  }
  
  if (toogleRender) {
    cout<<"toogle Render\n";
    glutPostRedisplay();
  }
}

void display()
{
  /* clear the color buffer (resets everything to black) */
  glClear(GL_COLOR_BUFFER_BIT);
  
  renderBattleField(USER_LEFT_OFFSET, TOP_OFFSET, 0);
  renderBattleField(ENEMY_LEFT_OFFSET, TOP_OFFSET, 1);
  
  renderButtons();
  
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
