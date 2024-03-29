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
#define BLADE2 0.5, -.08, 5.5
#define BLADE3 -0.5, -.08, 5.5
#define BLADE4 -1, .08, 1.2
#define BLADE5 1, .08, 1.2
#define BLADE6 0.5, .08, 5.5
#define BLADE7 -0.5, .08, 5.5

float viewX = 10;
float viewY = -15;
float viewZ = 7;

float millAngle = 0;
float millSpeed = 0;

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
  gluPerspective(45, (float)HEIGHT / (float)WIDTH, 1, 100);

  glViewport(0, 0, w, h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void display() // display function
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(viewX, viewY, viewZ, 0, 0, viewZ, 0, 0, 1);

  GLUquadricObj *cylinderFill;
  cylinderFill = gluNewQuadric();
  gluQuadricDrawStyle(cylinderFill, GLU_FILL);

  GLUquadricObj *diskFill, *diskLine;
  diskFill = gluNewQuadric();
  gluQuadricDrawStyle(diskFill, GLU_FILL);
  diskLine = gluNewQuadric();
  gluQuadricDrawStyle(diskLine, GLU_SILHOUETTE);

  // create ground
  glColor3f(0.5, 0.35, 0.05); // set brown color
  gluDisk(diskFill, 0, 15, 50, 50);
  glColor3f(0, 0, 0);
  gluDisk(diskLine, 0, 15, 50, 50);

  // create tower of the windmill
  glColor3f(0.7, 0.7, 0.7);
  gluCylinder(cylinderFill, 0.7, 0.7, 2.5, 50, 50);

  glColor3f(0, 0, 0);
  gluDisk(diskLine, 0, 0.7, 50, 50);
  glTranslatef(0, 0, 2.5);
  gluDisk(diskLine, 0, 0.7, 50, 50);

  glColor3f(0.7, 0.7, 0.7);
  gluCylinder(cylinderFill, 0.6, 0.6, 2.5, 50, 50);

  glColor3f(0, 0, 0);
  gluDisk(diskLine, 0, 0.6, 50, 50);
  glTranslatef(0, 0, 2.5);
  gluDisk(diskLine, 0, 0.6, 50, 50);

  glColor3f(0.7, 0.7, 0.7);
  gluCylinder(cylinderFill, 0.5, 0.5, 2.5, 50, 50);
  glColor3f(0, 0, 0);
  gluDisk(diskLine, 0, 0.5, 50, 50);
  glTranslatef(0, 0, 2.5);
  gluDisk(diskLine, 0, 0.5, 50, 50);
  glTranslatef(0, 0, -2.5);

  // create nacelle of the windmill
  glColor3f(0.5, 0.5, 0.5); // set nacelle color

  glTranslatef(0, 1, 3);
  glRotatef(90, 1, 0, 0);
  gluCylinder(cylinderFill, 1, 1, 2, 50, 50);

  glColor3f(0.5, 0.5, 0.5);
  gluDisk(diskFill, 0, 1, 50, 50);
  glColor3f(0, 0, 0);
  gluDisk(diskLine, 0, 1, 50, 50);

  glTranslatef(0, 0, 2);
  glColor3f(0.5, 0.5, 0.5);
  gluDisk(diskFill, 0, 1, 50, 50);
  glColor3f(0, 0, 0);
  gluDisk(diskLine, 0, 1, 50, 50);

  // create rotor of the windmill
  glColor3f(0.5, 0.5, 0.5);
  gluCylinder(cylinderFill, 0.1, 0.1, 0.5, 10, 10);
  glTranslatef(0, 0, 0.5);
  gluDisk(diskFill, 0, 0.1, 50, 10);
  glColor3f(0, 0, 0);
  gluDisk(diskLine, 0, 0.1, 50, 10);

  // create blades of the windmill
  glTranslatef(0, 0, -0.3);
  glRotatef(90, 1, 0, 0);

  glRotatef(millAngle, 0, 1, 0); // rotate the blades

  for (int i = 0; i < 4; i++)
  {
    gluDisk(diskLine, 0, 0.1, 10, 10);
    glColor3f(0.7, 0.7, 0.7); // set blade color
    gluCylinder(cylinderFill, 0.1, 0, 3, 10, 10);

    // create blades

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

    // create blade outlines

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);

    glVertex3f(BLADE0);
    glVertex3f(BLADE1);

    glVertex3f(BLADE1);
    glVertex3f(BLADE2);

    glVertex3f(BLADE2);
    glVertex3f(BLADE3);

    glVertex3f(BLADE3);
    glVertex3f(BLADE0);

    glVertex3f(BLADE4);
    glVertex3f(BLADE5);

    glVertex3f(BLADE5);
    glVertex3f(BLADE6);

    glVertex3f(BLADE6);
    glVertex3f(BLADE7);

    glVertex3f(BLADE7);
    glVertex3f(BLADE4);

    glVertex3f(BLADE0);
    glVertex3f(BLADE4);

    glVertex3f(BLADE1);
    glVertex3f(BLADE5);

    glVertex3f(BLADE2);
    glVertex3f(BLADE6);

    glVertex3f(BLADE3);
    glVertex3f(BLADE7);

    glEnd();

    glRotatef(-15, 0, 0, 1);
    glRotatef(90, 0, 1, 0);
  }
  gluDeleteQuadric(cylinderFill);
  gluDeleteQuadric(diskFill);
  gluDeleteQuadric(diskLine);

  glutSwapBuffers();
  rotate();
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
    if (millSpeed > -2)
      millSpeed -= 0.1;
    break;

  case GLUT_KEY_LEFT:
    if (millSpeed < 2)
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
  glEnable(GL_LINE_SMOOTH);

  glutReshapeFunc(reshape);
  glutDisplayFunc(display);

  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialkeyboard);

  glutMainLoop();

  return EXIT_SUCCESS;
}