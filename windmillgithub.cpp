#include <stdlib.h>
#include <iostream>
#include <GLUT/glut.h>
#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>

#define BLADE0 -1, -.08, 1.2
#define BLADE1 1, -.08, 1.2
#define BLADE2 1, -.08, 5.5
#define BLADE3 -1, -.08, 5.5
#define BLADE4 -1, .08, 1.2
#define BLADE5 1, .08, 1.2
#define BLADE6 1, .08, 5.5
#define BLADE7 -1, .08, 5.5

float viewX = 0;
float viewY = 0;
float viewZ = 0;

float millAngle = 0;
float millSpeed = 0;

void rotate()
{
  millAngle += millSpeed;
  millAngle = fmodf(millAngle, 360);
  glutPostRedisplay();
}

void reshape(int w, int h)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(55, 1.777777, 1, 50);

  glViewport(0, 0, w, h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(viewX, viewY, viewZ, 0, 0, viewZ, 0, 0, 1);

  GLUquadricObj *cylinder;
  cylinder = gluNewQuadric();
  GLUquadricObj *disk;
  disk = gluNewQuadric();

  gluQuadricTexture(cylinder, GLU_TRUE);
  gluQuadricNormals(cylinder, GLU_SMOOTH);
  gluQuadricDrawStyle(cylinder, GLU_FILL);
  gluQuadricTexture(disk, GLU_TRUE);
  gluQuadricNormals(disk, GLU_SMOOTH);
  gluQuadricDrawStyle(disk, GLU_FILL);

  glColor3f(0.5, 0.35, 0.05);   // set brown color
  gluDisk(disk, 0, 15, 50, 50); // ground

  glColor3f(0.5, 0.5, 0.5); // set grey color

  // create base of the windmill
  gluCylinder(cylinder, 0.7, 0.7, 2.5, 50, 50);
  glTranslatef(0, 0, 2.5);
  gluCylinder(cylinder, 0.6, 0.6, 2.5, 50, 50);
  glTranslatef(0, 0, 2.5);
  gluCylinder(cylinder, 0.5, 0.5, 2.5, 50, 50);
  glTranslatef(0, 0, 2.5);
  gluCylinder(cylinder, 0.4, 0.4, 2.5, 50, 50);

  // create wings of the windmill
  glTranslatef(0, 0, 2);

  glRotatef(90, 1, 0, 0);

  glRotatef(millAngle, 0, 0, 1);

  gluCylinder(cylinder, .15, .15, 1.5, 10, 10);
  gluDisk(disk, 0, .15, 10, 10);

  glColor3f(0.6, 0.5, 0.5); // set wing color
  glTranslatef(0, 0, 1);
  glRotatef(90, 1, 0, 0);

  for (int i = 0; i < 4; i++)
  {
    gluCylinder(cylinder, .1, 0, 3, 10, 10);

    glRotatef(15, 0, 0, 1);

    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(BLADE0);
    glTexCoord2f(1, 0);
    glVertex3f(BLADE1);
    glTexCoord2f(1, 3);
    glVertex3f(BLADE2);
    glTexCoord2f(0, 3);
    glVertex3f(BLADE3);

    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(BLADE7);
    glTexCoord2f(1, 0);
    glVertex3f(BLADE6);
    glTexCoord2f(1, 3);
    glVertex3f(BLADE5);
    glTexCoord2f(0, 3);
    glVertex3f(BLADE4);

    glNormal3f(1, 0, 0);
    glTexCoord2f(0, 0);
    glVertex3f(BLADE0);
    glTexCoord2f(1, 0);
    glVertex3f(BLADE3);
    glTexCoord2f(1, 3);
    glVertex3f(BLADE7);
    glTexCoord2f(0, 3);
    glVertex3f(BLADE4);

    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, 0);
    glVertex3f(BLADE1);
    glTexCoord2f(1, 0);
    glVertex3f(BLADE5);
    glTexCoord2f(1, 3);
    glVertex3f(BLADE6);
    glTexCoord2f(0, 3);
    glVertex3f(BLADE2);

    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0);
    glVertex3f(BLADE0);
    glTexCoord2f(1, 0);
    glVertex3f(BLADE4);
    glTexCoord2f(1, 3);
    glVertex3f(BLADE5);
    glTexCoord2f(0, 3);
    glVertex3f(BLADE1);

    glNormal3f(0, 0, -1);
    glTexCoord2f(0, 0);
    glVertex3f(BLADE3);
    glTexCoord2f(1, 0);
    glVertex3f(BLADE2);
    glTexCoord2f(1, 3);
    glVertex3f(BLADE6);
    glTexCoord2f(0, 3);
    glVertex3f(BLADE7);
    glEnd();

    glRotatef(90, 0, 1, 0);
  }
  gluDeleteQuadric(cylinder);
  gluDeleteQuadric(disk);
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
  if (key == 27)
    exit(0);
  switch (key)
  {
  case 113:
    viewX++;
    break;
  case 97:
    viewX--;
    break;
  case 119:
    viewY++;
    break;
  case 115:
    viewY--;
    break;
  case 101:
    viewZ++;
    break;
  case 100:
    viewZ--;
    break;
  default:
    break;
  }
}

void specialkeyboard(int key, int x, int y)
{
  switch (key)
  {
  case GLUT_KEY_LEFT:
    if (millSpeed > -1)
      millSpeed -= 0.1;
    break;
  case GLUT_KEY_RIGHT:
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
  glutInitWindowSize(1920, 1080);

  glutCreateWindow("Scene");
  glClearColor(1, 1, 1, 0.0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_NORMALIZE);

  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(rotate);

  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialkeyboard);

  glutMainLoop();

  return EXIT_SUCCESS;
}