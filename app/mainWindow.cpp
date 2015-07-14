#include "mainWindow.h"

#include "robot.h"

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


namespace w2s {
  /*********** GLOBALS ***********/
  int Width = 640;
  int Height = 480;
  int Window = 0;
  /*******************************/
    
  void drawRobot()
  {
    glTranslatef(0.0f, -3.0f, 10);
    glRotatef(robot::angle[TRONCO_Y], 0.0f, 1.0f, 0.0f);
    robot::tronco();

    robot::CabecaCompleta();
    robot::Ombros();

    robot::BracoDireitoCompleto();
    robot::BracoEsquerdoCompleto();
 
    robot::ArticulacoesDaCoxa();
    robot::PernaDireita();
    robot::PernaEsquerda();
  }

  void keyPressed(unsigned char key, int x, int y)
  {
    switch (key) {
    case ESC_KEY:
      glutDestroyWindow(Window);
      exit(0);
      break;
    case A_KEY:
      robot::rotateLeft();
      break;
    case D_KEY:
      robot::rotateRight();
      break;
    case S_KEY:
      if (robot::estadoAtual == WALKING)
        robot::stop();
      else
        robot::walk();
      break;
    case W_KEY:
      if (robot::estadoAtual == STOPPED)
        robot::walk();
      else
        robot::run();
      break;
    default:
      printf("Teclaram: %d\n", key);
      break;
    }
  }

  void keyPressed(int key, int x, int y)
  {
    switch (key) {
    case GLUT_KEY_UP:
      glutFullScreen();
      break;
    case GLUT_KEY_DOWN:
      glutReshapeWindow(Width, Height);
      break;
    default:
      printf("Teclaram: %d\n", key);
      break;
    }
  }

  void drawScene() 
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.0f);

    gluLookAt( //void gluLookAt (
      0.0f,     //    GLdouble eyex, 
      0.0f,     //    GLdouble eyey, 
      8.0f,     //    GLdouble eyez, 
      0.0f,     //    GLdouble centerx, 
      0.0f,     //    GLdouble centery, 
      0.0f,     //    GLdouble centerz, 
      0.0f,     //    GLdouble upx, 
      1.0f,     //    GLdouble upy, 
      0.0f);    //    GLdouble upz);

    drawRobot();

    glutSwapBuffers();
  }

  void show()
  { 
    robot::prepareAngles();
    glEnable(GL_LIGHT0);

    glutPostRedisplay();
  }

  void reshape(int width, int height)
  {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // perspective rate
    if (width <= height)
      glOrtho(-10.0f, 10.0f, -10.0f * (GLfloat)height / (GLfloat)width,
      10.0f * (GLfloat)height / (GLfloat)width, -10.0f, 10.0f);
    else
      glOrtho(-10.0f * (GLfloat)width / (GLfloat)height,
      10.0f * (GLfloat)width / (GLfloat)height, -10.0f, 10.0f, -10.0f, 10.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }
}

MainWindow::~MainWindow()
{

}

MainWindow::MainWindow(int argc, char *argv[])
{  
  /**
   * Initialize GLUT state - glut will take any command line arguments that pertain to it or
   * X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html 
   */
  glutInit(&argc, argv);  
  setup();
  init();
  
  glutReshapeFunc(w2s::reshape);
  glutDisplayFunc(w2s::drawScene);
  glutKeyboardFunc(w2s::keyPressed);
  glutSpecialFunc(w2s::keyPressed);
  glutIdleFunc(w2s::show);
}

void MainWindow::init()
{  
  w2s::robot::init();
}

int MainWindow::run()
{
  /* Iniciamos a maquina de processamento de eventos do GLUT. */
  glutMainLoop();
  return 0;
}

int MainWindow::setup()
{
  /**
   * Select type of Display mode:
   * Double buffer
   * RGBA color
   * Alpha components supported
   * Depth buffer
   */
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(-1, -1);
  glutInitWindowSize(w2s::Width, w2s::Height);
  w2s::Window = glutCreateWindow(std::string("ine5341 Computação Gráfica UFSC").c_str());

  createLight();

  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  return TRUE; // Fazemos de conta que sempre dá tudo certo retornando OK
}

void MainWindow::createLight()
{
  GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
  GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat light_position[] = { 10.0f, 0.0f, 10.0f, 0.0f };

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}
