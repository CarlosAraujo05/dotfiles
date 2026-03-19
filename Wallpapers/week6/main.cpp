
#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

int alpha = 0, beta = 45, r = 50;

const int N = 10;
GLuint buffers[N];
unsigned int t, tw, th;
unsigned char *imageData;

void changeSize(int w, int h) {

  // Prevent a divide by zero, when window is too short
  // (you cant make a window with zero width).
  if (h == 0)
    h = 1;

  // compute window's aspect ratio
  float ratio = w * 1.0 / h;

  // Reset the coordinate system before modifying
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set the viewport to be the entire window
  glViewport(0, 0, w, h);

  // Set the correct perspective
  gluPerspective(45, ratio, 1, 1000);

  // return to the model view matrix mode
  glMatrixMode(GL_MODELVIEW);
}

void drawTerrain() {

  // colocar aqui o código de desnho do terreno usando VBOs com TRIANGLE_STRIPS
  glEnableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  for (int i = 0; i < tw - 1; i++) {
    glDrawArrays(GL_TRIANGLE_STRIP, i * th * 2, th * 2);
  }
}

void renderScene(void) {

  float pos[4] = {-1.0, 1.0, 1.0, 0.0};

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

  drawTerrain();

  // just so that it renders something before the terrain is built
  // to erase when the terrain is ready
  glutWireTeapot(2.0);

  // End of frame
  glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy) {

  // put code to process regular keys in here
}

void processMouseButtons(int button, int state, int xx, int yy) {

  if (state == GLUT_DOWN) {
    startX = xx;
    startY = yy;
    if (button == GLUT_LEFT_BUTTON)
      tracking = 1;
    else if (button == GLUT_RIGHT_BUTTON)
      tracking = 2;
    else
      tracking = 0;
  } else if (state == GLUT_UP) {
    if (tracking == 1) {
      alpha += (xx - startX);
      beta += (yy - startY);
    } else if (tracking == 2) {

      r -= yy - startY;
      if (r < 3)
        r = 3.0;
    }
    tracking = 0;
  }
}

void processMouseMotion(int xx, int yy) {

  int deltaX, deltaY;
  int alphaAux, betaAux;
  int rAux;

  if (!tracking)
    return;

  deltaX = xx - startX;
  deltaY = yy - startY;

  if (tracking == 1) {

    alphaAux = alpha + deltaX;
    betaAux = beta + deltaY;

    if (betaAux > 85.0)
      betaAux = 85.0;
    else if (betaAux < -85.0)
      betaAux = -85.0;

    rAux = r;
  } else if (tracking == 2) {

    alphaAux = alpha;
    betaAux = beta;
    rAux = r - deltaY;
    if (rAux < 3)
      rAux = 3;
  }
  camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
  camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
  camY = rAux * sin(betaAux * 3.14 / 180.0);
}
float h(int i, int j) {
  return imageData[i * tw + j] / 255.0 *
         30.0; // scale the height to be between 0 and 30
}

void init() {

  // 	Load the height map "terreno.jpg"
  ilGenImages(1, &t);
  ilBindImage(t);
  // terreno.jpg is the image containing our height map
  ilLoadImage((ILstring) "terreno.jpg");
  // convert the image to single channel per pixel
  // with values ranging between 0 and 255
  ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
  // important: check tw and th values
  // both should be equal to 256
  // if not there was an error loading the image
  // most likely the image could not be found
  tw = ilGetInteger(IL_IMAGE_WIDTH);
  th = ilGetInteger(IL_IMAGE_HEIGHT);

  if (tw != 256 || th != 256) {
    printf("Error loading the height map image\n");
    exit(0);
  }
  // imageData is a LINEAR array with the pixel values
  imageData = ilGetData();
  // 	Build the vertex arrays
  std::vector<float> v;
  for (int i = 0; i < tw; i++) {
    for (int j = 0; j < th; j++) {
      v.push_back(i - tw / 2.0f); // center the terrain at the origin
      v.push_back(h(i, j));
      v.push_back(j - th / 2.0f);

      v.push_back(i + 1 - tw / 2.0f); // center the terrain at the origin
      v.push_back(h(i + 1, j));
      v.push_back(j - th / 2.0f);
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(float), v.data(),
               GL_STATIC_DRAW);
  // 	OpenGL settings
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // glEnable(GL_CULL_FACE);
}

int main(int argc, char **argv) {

  // init GLUT and the window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(800, 600);
  glutCreateWindow("CG@DI-UM");

  // Required callback registry
  glutDisplayFunc(renderScene);
  glutIdleFunc(renderScene);
  glutReshapeFunc(changeSize);

  // Callback registration for keyboard processing
  glutKeyboardFunc(processKeys);
  glutMouseFunc(processMouseButtons);
  glutMotionFunc(processMouseMotion);

  glewInit();               // initialize GLEW
  glGenBuffers(N, buffers); // create N buffers
  ilInit();                 // initialize DevIL
  init();

  // enter GLUT's main cycle
  glutMainLoop();

  return 0;
}
