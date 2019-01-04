/* This line is for Max OSX  */
#include <GLUT/glut.h>
#include <iostream>

/*! GLUT display callback function */
void display(void);
/*! GLUT window reshape callback function */
void reshape(int, int);

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  
  /* set the window size to 512 x 512 */
  glutInitWindowSize(1024, 512);
  
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

void renderBattleField(int originX, int originY, int size=400)
{
  printf("%d %d %d\n",originX, originY, size);
  glBegin(GL_LINE_LOOP);
  
  glVertex2f(originX, originY);
  glVertex2f(size+originX, originY);
  glVertex2f(size+originX, size+originY);
  glVertex2f(originX, size+originY);
  
  glEnd();
  
  int stepSize = size/10;
  
  glBegin(GL_LINES);
  for (int i=0; i<=size; i+=stepSize) {
    glVertex2f(originX, i+originY);
    glVertex2f(size+originX, i+originY);
    glVertex2f(i+originX, originY);
    glVertex2f(i+originX, size+originY);
  }
  glEnd();
}

/*! glut display callback function.  Every time the window needs to be drawn,
 glut will call this function.  This includes when the window size
 changes, or when another window covering part of this window is
 moved so this window is uncovered.
 */
void display()
{
  /* clear the color buffer (resets everything to black) */
  glClear(GL_COLOR_BUFFER_BIT);
  
  /* set the current drawing color to red */
  glColor3f(1, 0, 0);
  
  renderBattleField(10, 10);
  
  glColor3f(1, 1, 1);
  renderBattleField(500, 10);
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
  gluOrtho2D(0,width,0,height);
  
  /* switch back to the model view matrix */
  glMatrixMode(GL_MODELVIEW);
}
