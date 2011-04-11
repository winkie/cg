#include "demoWindow.h"

#include "cSphere.h"

DemoWindow::DemoWindow(GlutMaster * glutMaster,
                       int setWidth, int setHeight,
                       int setInitPositionX, int setInitPositionY,
                       char * title)
{
   memset(keys, 0, 256 * sizeof(bool));
   mMouseLeft = false;
   mMouseDX = mMouseDY = 0;
   mCamera.set(Eigen::Vector3f(0, 0, -100), Eigen::Vector3f(0, 0, 0));
   width  = setWidth;               
   height = setHeight;

   initPositionX = setInitPositionX;
   initPositionY = setInitPositionY;

   glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(width, height);
   glutInitWindowPosition(initPositionX, initPositionY);
   glViewport(0, 0, width, height);   // This may have to be moved to after the next line on some platforms

   glutMaster->CallGlutCreateWindow(title, this);

   glutMaster->SetIdleToCurrentWindow();
   glutMaster->EnableIdleFunction();
   glutIgnoreKeyRepeat(true);

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glEnable(GL_COLOR_MATERIAL);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glCullFace(GL_FRONT_AND_BACK);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glClearColor(0, 0, 0, 1.0f);
   glClearDepth(1.0f);
   glColor4f(1.0, 0.0, 0.0, 1.0);
}

DemoWindow::~DemoWindow()
{
   glutDestroyWindow(windowID);
}

void DemoWindow::CallBackDisplayFunc(void)
{
   static cSphere sphere1(3.5f, Eigen::Vector3f(1, 0, 0), Eigen::Vector3f(0, 0, 0));
   static cSphere sphere2(1.5f, Eigen::Vector3f(0, 1, 0), Eigen::Vector3f(0, 0, 5));
   static cSphere sphere3(1.0f, Eigen::Vector3f(0, 0, 1), Eigen::Vector3f(-4, -4, 0));
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   mCamera.setupMatrix();

   glPushMatrix();
   glTranslatef(0, 5, 0);
   glBegin(GL_TRIANGLES);
      glColor3f(1.0f,0.0f,0.0f);	      // Red
      glVertex3f(0.0f, 1.0f, 0.0f);    // Top Of Triangle (Front)
      glColor3f(0.0f,1.0f,0.0f);       // Green
      glVertex3f(-1.0f,-1.0f, 0.0f);   // Left Of Triangle (Front)
      glColor3f(0.0f,0.0f,1.0f);       // Blue
      glVertex3f(1.0f,-1.0f, 0.0f);    // Right Of Triangle (Front)
   glEnd();
   glPopMatrix();
   
   sphere1.render();
   sphere2.render();
   sphere3.render();

   glutSwapBuffers();
}

void DemoWindow::CallBackReshapeFunc(int w, int h)
{
   width = w;
   height= h;

   if (h == 0)
      h = 1;

   glViewport(0, 0, width, height); 
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 1000.0f);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glutPostRedisplay();
}

void DemoWindow::CallBackKeyboardFunc(unsigned char key, int x, int y)
{
   keys[key] = true;
   if (key == 27)   //ESC
   {
      //glutDestroyWindow(GetWindowID());
      glutLeaveMainLoop();
   }
}

void DemoWindow::CallBackIdleFunc(void)
{
//   glRotatef(0.25, 1, 1, 2);
   if (mMouseLeft)
      mCamera.rotate(mMouseDX, mMouseDY);
   mMouseDY = mMouseDX = 0;

   if (keys['w'])
      mCamera.move(0.1f);
   if (keys['a'])
      mCamera.strafe(-0.1f);
   if (keys['s'])
      mCamera.move(-0.1f);
   if (keys['d'])
      mCamera.strafe(0.1f);
   glutPostRedisplay();
}   

void DemoWindow::CallBackMouseFunc( int button, int state, int x, int y )
{
   if (button == GLUT_LEFT_BUTTON)
   {
      mMouseLeft = (state == GLUT_DOWN);
   }
}

void DemoWindow::CallBackMotionFunc( int x, int y )
{
   mMouseDX = x - mPrevMouseX;
   mMouseDY = y - mPrevMouseY;
   mPrevMouseX = x, mPrevMouseY = y;
}

void DemoWindow::CallBackPassiveMotionFunc( int x, int y )
{
   mMouseDX = x - mPrevMouseX;
   mMouseDY = y - mPrevMouseY;
   mPrevMouseX = x, mPrevMouseY = y;
}

void DemoWindow::CallBackKeyboardUpFunc( unsigned char key, int x, int y )
{
   keys[key] = false;
}






