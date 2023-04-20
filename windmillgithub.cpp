#include <stdlib.h>
#include <iostream>
#include <GLUT/glut.h>
#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>

using namespace std;

#define HEIGHT 1920
#define WIDTH 1080

#define BLADE0 -1, -.08, 1.2
#define BLADE1 1, -.08, 1.2
#define BLADE2 1, -.08, 5.5
#define BLADE3 -1, -.08, 5.5
#define BLADE4 -1, .08, 1.2
#define BLADE5 1, .08, 1.2
#define BLADE6 1, .08, 5.5
#define BLADE7 -1, .08, 5.5

float viewX = 10;
float viewY = -15;
float viewZ = 7;

float millAngle = 0;
float millSpeed = 0;

void displayData()
{
  glRasterPos2f(10, 10);

  const char *text = "Hello, World!";
  for (int i = 0; i < strlen(text); i++)
  {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
  }
}

void rotate() // rotate the windmill
{
  millAngle += millSpeed;
  millAngle = fmodf(millAngle, 360);
  glutPostRedisplay();
}

void reshape(int w, int h) // reshape the window
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(55, (float)HEIGHT / (float)WIDTH, 1, 50);

  glViewport(0, 0, w, h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void display(void) // display function
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glColor3f(0, 0, 0);
  displayData();

  gluLookAt(viewX, viewY, viewZ, 0, 0, viewZ, 0, 0, 1);

  GLUquadricObj *cylinder;
  cylinder = gluNewQuadric();
  gluQuadricDrawStyle(cylinder, GLU_FILL);
  GLUquadricObj *disk;
  disk = gluNewQuadric();
  gluQuadricDrawStyle(disk, GLU_FILL);

  // create ground
  glColor3f(0.5, 0.35, 0.05); // set brown color
  gluDisk(disk, 0, 15, 50, 50);

  // create tower of the windmill
  glColor3f(0.7, 0.7, 0.7);
  gluCylinder(cylinder, 0.7, 0.7, 2.5, 50, 50);
  glTranslatef(0, 0, 2.5);
  gluCylinder(cylinder, 0.6, 0.6, 2.5, 50, 50);
  glTranslatef(0, 0, 2.5);
  gluCylinder(cylinder, 0.5, 0.5, 2.5, 50, 50);

  // create nacelle of the windmill
  glColor3f(0.5, 0.5, 0.5); // set nacelle color
  glTranslatef(0, 1, 3);
  glRotatef(90, 1, 0, 0);
  gluCylinder(cylinder, 1, 1, 2, 50, 50);
  gluDisk(disk, 0, 1, 50, 50);
  glTranslatef(0, 0, 2);
  gluDisk(disk, 0, 1, 50, 50);

  // create rotor of the windmill
  gluCylinder(cylinder, 0.1, 0.1, 0.5, 10, 10);
  glTranslatef(0, 0, 0.5);
  gluDisk(disk, 0, 0.1, 10, 10);

  // create blades of the windmill
  glColor3f(0.6, 0.5, 0.5); // set blade color
  glTranslatef(0, 0, -0.3);
  glRotatef(90, 1, 0, 0);

  glRotatef(millAngle, 0, 1, 0); // rotate the blades

  for (int i = 0; i < 4; i++)
  {
    gluCylinder(cylinder, .1, 0, 3, 10, 10);

    glRotatef(15, 0, 0, 1);
    glBegin(GL_QUADS);

    glVertex3f(BLADE0);
    glVertex3f(BLADE1);
    glVertex3f(BLADE2);
    glVertex3f(BLADE3);

    glVertex3f(BLADE7);
    glVertex3f(BLADE6);
    glVertex3f(BLADE5);
    glVertex3f(BLADE4);

    glVertex3f(BLADE0);
    glVertex3f(BLADE3);
    glVertex3f(BLADE7);
    glVertex3f(BLADE4);

    glVertex3f(BLADE1);
    glVertex3f(BLADE5);
    glVertex3f(BLADE6);
    glVertex3f(BLADE2);

    glVertex3f(BLADE0);
    glVertex3f(BLADE4);
    glVertex3f(BLADE5);
    glVertex3f(BLADE1);

    glVertex3f(BLADE3);
    glVertex3f(BLADE2);
    glVertex3f(BLADE6);
    glVertex3f(BLADE7);

    glEnd();

    glRotatef(-15, 0, 0, 1);
    glRotatef(90, 0, 1, 0);
  }
  gluDeleteQuadric(cylinder);
  gluDeleteQuadric(disk);

  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) // keyboard function
{
  if (key == 27) // escape key
    exit(0);
  switch (key)
  {
  case 113: // q
    viewX++;
    break;
  case 97: // a
    viewX--;
    break;
  case 119: // w
    viewY++;
    break;
  case 115: // s
    viewY--;
    break;
  case 101: // e
    viewZ++;
    break;
  case 100: // d
    viewZ--;
    break;
  default:
    cout << "Invalid key" << endl;
    break;
  }
}

void specialkeyboard(int key, int x, int y)
{
  switch (key)
  {
  case GLUT_KEY_RIGHT:
    if (millSpeed > -1)
      millSpeed -= 0.1;
    break;

  case GLUT_KEY_LEFT:
    if (millSpeed < 1)
      millSpeed += 0.1;
    break;
  }
}

int main(int argc, char **argv)
{
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(HEIGHT, WIDTH);

  glutCreateWindow("Computer Graphics Project");
  glClearColor(1, 1, 1, 0);

  glEnable(GL_DEPTH_TEST);

  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(rotate);

  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialkeyboard);

  glutMainLoop();

  return EXIT_SUCCESS;
}