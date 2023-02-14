#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>

#include "DLASystem.h"
#include "Window.h"


// functions which are needed for openGL go into a namespace so that we can identify them
namespace drawFuncs {
  void handleKeypress(unsigned char key, int x, int y);
  void display(void);
  void update(int val);
  void introMessage();
}

// this is a global pointer, which is how we access the system itself
DLASystem *sys;

int main(int argc, char **argv) {
  // turn on glut
	glutInit(&argc, argv);

  int window_size[] = { 480,480 };
  std::string window_title("simple DLA simulation");

  // create a window
  Window *win = new Window(window_size,window_title);

  // create the system
  sys = new DLASystem(win);

  // this is the seed for the random numbers
  int seed = 6;
  std::cout << "setting seed " << seed << std::endl;
  sys->setSeed(seed);

  // print the "help" message to the console
  drawFuncs::introMessage();

  // tell openGL how to redraw the screen and respond to the keyboard
	glutDisplayFunc(  drawFuncs::display );
	glutKeyboardFunc( drawFuncs::handleKeypress );

  // tell openGL to do its first update after waiting 10ms
  int wait = 10;
  int val = 0;
	glutTimerFunc(wait, drawFuncs::update, val);

  // start the openGL stuff
 	glutMainLoop();

  return 0;
}

// this is just a help message
void drawFuncs::introMessage() {
        std::cout << "Keys (while in graphics window):" << std::endl << "  q or e to quit (or exit)" << std::endl;
        std::cout << "  h to print this message (help)" << std::endl;
        std::cout << "  u for a single update" << std::endl;
        std::cout << "  g to start running (go)" << std::endl;
        std::cout << "  p to pause running" << std::endl;
        std::cout << "  s to run in slow-mode" << std::endl;
        std::cout << "  f to run in fast-mode" << std::endl;
        std::cout << "  r to clear everything (reset)" << std::endl;
        std::cout << "  z to pause and zoom in" << std::endl;
        std::cout << "  w or b to change background colour to white or black" << std::endl;
}

// openGL function deals with the keyboard
void drawFuncs::handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
  case 'h':
    drawFuncs::introMessage();
    break;
	case 'q':
	case 'e':
		std::cout << "Exiting..." << std::endl;
    // delete the system
    delete sys;
		exit(0);
		break;
  case 'p':
    std::cout << "pause" << std::endl;
    sys->pauseRunning();
    break;
  case 'g':
    std::cout << "go" << std::endl;
    sys->setRunning();
    glutTimerFunc(0, drawFuncs::update, 0);
    break;
  case 's':
    std::cout << "slow" << std::endl;
    sys->setSlow();
    break;
  case 'w':
    std::cout << "white" << std::endl;
    sys->setWinBackgroundWhite();
    break;
  case 'b':
    std::cout << "black" << std::endl;
    sys->setWinBackgroundBlack();
    break;
  case 'f':
    std::cout << "fast" << std::endl;
    sys->setFast();
    break;
  case 'r':
    std::cout << "reset" << std::endl;
    sys->Reset();
    break;
  case 'z':
    std::cout << "zoom" << std::endl;
    sys->pauseRunning();
    sys->viewAddCircle();
    break;
  case 'u':
    std::cout << "upd" << std::endl;
    sys->Update();
    break;
	}
  // tell openGL to redraw the window
	glutPostRedisplay();
}

// this function gets called whenever the algorithm should do its update
void drawFuncs::update(int val) {
  int wait;  // time to wait between updates (milliseconds)

  if ( sys->running ) {
    if ( sys->slowNotFast == 1)
      wait = 10;
    else
      wait = 0;

    sys->Update();

    // tell openGL to call this funtion again after "wait" milliseconds
    glutTimerFunc(wait, drawFuncs::update, 0);
  }

}

// this function redraws the window when necessary
void drawFuncs::display() {
    	//  Clear the window or more specifically the frame buffer...
      //  This happens by replacing all the contents of the frame
      //  buffer by the clear color (black in our case)
      glClear(GL_COLOR_BUFFER_BIT);

      // this puts the camera at the origin (not sure why) with (I think) z axis out of page and y axis up
      // there is also the question of the GL perspective which is not set up in any clear way at the moment
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0.0, 0.0, 1.0,   /* camera position */
        0.0, 0.0, -1.0,        /* point to look at */
        0.0, 1.0, 0.0);		   /* up direction */

      //sys->DrawSpheres();
      sys->DrawSquares();

      //  Swap contents of backward and forward frame buffers
      glutSwapBuffers();
}

