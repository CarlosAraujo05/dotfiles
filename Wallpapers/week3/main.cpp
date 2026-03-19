#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
float camRadius = 10.0f; // distância ao centro
float camAzim = 45.0f;   // ângulo horizontal
float camElev = 30.0f;   // ângulo vertical
float camSpeed = 5.0f;   // velocidade de rotação em graus
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

void drawCylinder(float radius, float height, int slices) {

  float slice = 2 * M_PI / slices; // usar radianos!

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(1.0f, 1.0f, 1.0f);

  float half = height / 2.0f;

  for (int i = 0; i < slices; i++) {

    float ang1 = i * slice;
    float ang2 = (i + 1) * slice;

    float x1 = radius * sin(ang1);
    float z1 = radius * cos(ang1);

    float x2 = radius * sin(ang2);
    float z2 = radius * cos(ang2);

    glBegin(GL_TRIANGLES);

    // Topo
    glVertex3f(0.0f, half, 0.0f);
    glVertex3f(x1, half, z1);
    glVertex3f(x2, half, z2);

    // Base
    glVertex3f(0.0f, -half, 0.0f);
    glVertex3f(x2, -half, z2);
    glVertex3f(x1, -half, z1);

    glEnd();

    // Lado (2 triângulos = 1 retângulo)
    glBegin(GL_TRIANGLES);

    // triângulo 1
    glVertex3f(x1, half, z1);
    glVertex3f(x1, -half, z1);
    glVertex3f(x2, -half, z2);

    // triângulo 2
    glVertex3f(x1, half, z1);
    glVertex3f(x2, -half, z2);
    glVertex3f(x2, half, z2);

    glEnd();
  }
}

void renderScene(void) {

  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // set the camera
  glLoadIdentity();
  float azimRad = camAzim * M_PI / 180.0f;
  float elevRad = camElev * M_PI / 180.0f;

  float camX = camRadius * cos(elevRad) * sin(azimRad);
  float camY = camRadius * sin(elevRad);
  float camZ = camRadius * cos(elevRad) * cos(azimRad);

  gluLookAt(camX, camY, camZ,  // posição da câmara
            0.0f, 0.0f, 0.0f,  // ponto que olha (centro)
            0.0f, 1.0f, 0.0f); // vetor up

  drawCylinder(1, 2, 10);

  // End of frame
  glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {

  switch (c) {
  case 'w': // sobe a câmara
  case 'W':
    camElev += camSpeed;
    if (camElev > 89.0f)
      camElev = 89.0f;
    break;

  case 's': // desce a câmara
  case 'S':
    camElev -= camSpeed;
    if (camElev < -89.0f)
      camElev = -89.0f;
    break;

  case 'a': // gira à esquerda
  case 'A':
    camAzim -= camSpeed;
    break;

  case 'd': // gira à direita
  case 'D':
    camAzim += camSpeed;
    break;

  case '+': // aproxima (opcional)
    camRadius -= 0.5f;
    if (camRadius < 2.0f)
      camRadius = 2.0f;
    break;

  case '-': // afasta (opcional)
    camRadius += 0.5f;
    break;
  }

  glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {

  // put code to process special keys in here
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

  // enter GLUT's main cycle
  glutMainLoop();

  return 1;
}
