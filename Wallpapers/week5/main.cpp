#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;
float moveBlue = 0.0f, moverRed = 0.0f;
void spherical2Cartesian() {

  camX = radius * cos(beta) * sin(alfa);
  camY = radius * sin(beta);
  camZ = radius * cos(beta) * cos(alfa);
}

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

void createTree(int x, int z) {
  glColor3f(0.5f, 0.35f, 0.05f); // brown
  GLfloat base = 1.0f, height = 5.0f;
  GLint slices = 20, stacks = 20;
  glPushMatrix();
  glTranslatef(x, 0, z);
  glRotatef(-90, 1, 0, 0);
  glutSolidCone(base / 2, height, slices, stacks);
  glPushMatrix();
  glTranslatef(0, 0, height / 2);
  glColor3f(0.0f, 0.9f, 0.0f); // green
  glutSolidCone(base, height, slices, stacks);
  glPopMatrix();
  glPopMatrix();
}

void createForest() {
  srand(42);
  int numTrees = 150;
  while (numTrees > 0) {
    float x = rand() % 200 - 100;
    float z = rand() % 200 - 100;
    float dist = sqrt(x * x + z * z);
    if (dist > 50) {
      createTree(x, z);
      numTrees--;
    }
  }
}

void drawTeapots(int nTeapots, float radius, float size) {
  for (int i = 0; i < nTeapots; i++) {
    glPushMatrix();
    glRotatef(i * (360.0f / nTeapots) + moveBlue, 0, 1, 0);
    glTranslatef(radius, size, 0);
    glutSolidTeapot(size);
    glPopMatrix();
  }
}

void renderScene(void) {

  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // set the camera
  glLoadIdentity();
  gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

  glColor3f(0.2f, 0.8f, 0.2f);
  glBegin(GL_TRIANGLES);
  glVertex3f(100.0f, 0, -100.0f);
  glVertex3f(-100.0f, 0, -100.0f);
  glVertex3f(-100.0f, 0, 100.0f);

  glVertex3f(100.0f, 0, -100.0f);
  glVertex3f(-100.0f, 0, 100.0f);
  glVertex3f(100.0f, 0, 100.0f);
  glEnd();
  moveBlue += 0.1f;
  moverRed += 0.2f;
  // put code to draw scene in here
  createForest();
  glColor3f(0.0f, 0.0f, 1.0f); // blue
  drawTeapots(10, 35, 3);
  glColor3f(1.0f, 0.0f, 0.0f); // red
  drawTeapots(6, 15, 3);
  glColor3f(0.0f, 0.0f, 1.0f); // blue
  glutSolidTorus(2, 5, 20, 20);
  glutPostRedisplay();
  glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {

  // put code to process regular keys in here
}

void processSpecialKeys(int key, int xx, int yy) {

  switch (key) {

  case GLUT_KEY_RIGHT:
    alfa -= 0.1;
    break;

  case GLUT_KEY_LEFT:
    alfa += 0.1;
    break;

  case GLUT_KEY_UP:
    beta += 0.1f;
    if (beta > 1.5f)
      beta = 1.5f;
    break;

  case GLUT_KEY_DOWN:
    beta -= 0.1f;
    if (beta < -1.5f)
      beta = -1.5f;
    break;

  case GLUT_KEY_PAGE_DOWN:
    radius -= 1.0f;
    if (radius < 1.0f)
      radius = 1.0f;
    break;

  case GLUT_KEY_PAGE_UP:
    radius += 1.0f;
    break;
  }
  spherical2Cartesian();
  glutPostRedisplay();
}

void printInfo() {

  printf("Vendor: %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Version: %s\n", glGetString(GL_VERSION));

  printf("\nUse Arrows to move the camera up/down and left/right\n");
  printf("Home and End control the distance from the camera to the origin");
}

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

  // Callback registration for keyboard processing
  glutKeyboardFunc(processKeys);
  glutSpecialFunc(processSpecialKeys);

  //  OpenGL settings
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  spherical2Cartesian();
  printInfo();

  // enter GLUT's main cycle
  glutMainLoop();

  return 1;
}
