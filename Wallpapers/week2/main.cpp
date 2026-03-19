#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float posX = 0;
float posY = 0;
float posZ = 0;

float rotX = 0;
float rotY = 0;
float rotZ = 0;

void changeSize(int w, int h) {

  // Prevent a divide by zero, when window is too short
  // (you cant make a window with zero width).
  if (h == 0)
    h = 1;

  // compute window's aspect ratio
  float ratio = w * 1.0 / h;

  // Set the projection matrix as current
  glMatrixMode(GL_PROJECTION);
  // Load Identity Matrix
  glLoadIdentity();

  // Set the viewport to be the entire window
  glViewport(0, 0, w, h);

  // Set perspective
  gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

  // return to the model view matrix mode
  glMatrixMode(GL_MODELVIEW);
}

void actions(unsigned char key, int x, int y) {
  switch (key) {
  case 'w':
    posZ -= 0.2f;
    break;

  case 's':
    posZ += 0.2f;
    break;

  case 'a':
    posX -= 0.2f;
    break;

  case 'd':
    posX += 0.2f;
    break;
  }
  glutPostRedisplay();
}

void specialActions(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_UP:
    rotX -= 2;
    break;

  case GLUT_KEY_DOWN:
    rotZ += 2;
    break;

  case GLUT_KEY_LEFT:
    rotX -= 2;
    break;

  case GLUT_KEY_RIGHT:
    rotX += 2;
    break;
  }
  glutPostRedisplay();
}

void renderScene(void) {

  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  // set the camera
  gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

  // put axis drawing in here

  glBegin(GL_LINES);
  // eixo dos X
  glColor3f(1, 0, 0);
  glVertex3f(-100.0f, 0.0f, 0.0f);
  glVertex3f(100.0f, 0.0f, 0.0f);

  // eixo dos Y
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, -100.0f, 0.0f);
  glVertex3f(0.0f, 100.0f, 0.0f);

  // eixo dos Z
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, -100.0f);
  glVertex3f(0.0f, 0.0f, 100.0f);
  glEnd();

  // put pyramid drawing instructions here
  glTranslatef(posX, posY, posZ);
  glRotatef(rotX, 1, 0, 0);
  glRotatef(rotY, 0, 1, 0);
  glRotatef(rotZ, 0, 0, 1);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glColor3f(1, 2, 3);
  glBegin(GL_TRIANGLES);
  glVertex3f(-2.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 2.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, -2.0f);

  glVertex3f(0.0f, 0.0f, -2.0f);
  glVertex3f(0.0f, 2.0f, 0.0f);
  glVertex3f(2.0f, 0.0f, 0.0f);

  glVertex3f(2.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 2.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 2.0f);

  glVertex3f(0.0f, 0.0f, 2.0f);
  glVertex3f(0.0f, 2.0f, 0.0f);
  glVertex3f(-2.0f, 0.0f, 0.0f);

  glVertex3f(2.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 2.0f);
  glVertex3f(-2.0f, 0.0f, 0.0f);

  glVertex3f(2.0f, 0.0f, 0.0f);
  glVertex3f(-2.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, -2.0f);
  glEnd();

  // End of frame
  glutSwapBuffers();
}

// write function to process keyboard events

int main(int argc, char **argv) {

  // init GLUT and the window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(800, 800);
  glutCreateWindow("CG@DI-UM");

  // Required callback registry
  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);

  // put here the registration of the keyboard callbacks
  glutKeyboardFunc(actions);
  glutSpecialFunc(specialActions);

  //  OpenGL settings
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // enter GLUT's main cycle
  glutMainLoop();

  return 1;
}
