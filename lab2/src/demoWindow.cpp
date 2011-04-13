#define _USE_MATH_DEFINES
#include <cmath>

#include "demoWindow.h"
#include "cSphere.h"
#include "cPointLight.h"

const static float fovy = M_PI_4;

DemoWindow::DemoWindow(GlutMaster *glutMaster, int setWidth, int setHeight,
                       int setInitPositionX, int setInitPositionY, const char *title)
{
   memset(keys, 0, 256 * sizeof(bool));
   mMouseLeft = false;
   mMouseDX = mMouseDY = 0;
   mCamera.set(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(0, 0, 1));
   width = setWidth;
   height = setHeight;

   initPositionX = setInitPositionX;
   initPositionY = setInitPositionY;

   glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(width, height);
   glutInitWindowPosition(initPositionX, initPositionY);
   glViewport(0, 0, width, height); // This may have to be moved to after the next line on some platforms

   glutMaster->CallGlutCreateWindow(title, this);

   glutMaster->SetIdleToCurrentWindow();
   glutMaster->EnableIdleFunction();
   glutIgnoreKeyRepeat(true);
   
   mRenderer = &mPreviewRenderer;
   mRenderer->setupProjection(width, height, fovy);

   glClearDepth(1.0f);
   glColor4f(1.0, 0.0, 0.0, 1.0);

   sMaterial mat(Eigen::Vector3f(1, 0, 0));
   mat.mKAmbi = 0.2;
   mat.mKDiff = 0.5;
   mat.mKSpec = 0.7;
   mat.mKRefl = 1;
   //mat.mMedium = cRayTracer::mGlass;
   mScene.addLight(new cPointLight(Eigen::Vector3f(0, 0, 1),
         Eigen::Vector3f(-5, 10, 60), 15));
   mScene.addLight(new cPointLight(Eigen::Vector3f(0, 1, 0),
         Eigen::Vector3f(5, 10, 60), 15));

   mScene.addObject(new cSphere(1.5f, mat,
         Eigen::Vector3f(0, 0, 50)));
   //mScene.addObject(new cSphere(1.5f, Eigen::Vector3f(0, 1, 0),
   //      Eigen::Vector3f(0, 10, 50)));
   //mScene.addObject(new cSphere(1.5f, Eigen::Vector3f(0, 0, 1),
   //      Eigen::Vector3f(-4, -4, 50)));
   //mScene.addObject(new cSphere(1.5f, Eigen::Vector3f(0, 1, 1),
   //      Eigen::Vector3f(-4, 10, 50)));

   mScene.setBackground(0.3f, 0.3f, 0.3f);
}

DemoWindow::~DemoWindow()
{
   glutDestroyWindow(windowID);
}

void DemoWindow::CallBackDisplayFunc(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   mRenderer->render(mCamera, mScene);

   glutSwapBuffers();
}

void DemoWindow::CallBackReshapeFunc(int w, int h)
{
   width = w;
   height = h;

   if (h == 0)
      h = 1;

   mRenderer->setupProjection(w, h, fovy);

   glutPostRedisplay();
}

void DemoWindow::CallBackKeyboardFunc(unsigned char key, int x, int y)
{
   keys[key] = true;
   switch (key)
   //ESC
   {
   case 27: //ESC
      glutLeaveMainLoop();
      break;
   case 13: //ENTER
      switchRenderers();
      break;
   }
}

void DemoWindow::CallBackIdleFunc(void)
{
   if (mMouseLeft)
      mCamera.rotate(mMouseDX, mMouseDY);
   mMouseDY = mMouseDX = 0;

   if (keys['w'])
      mCamera.move(0.01f);
   if (keys['a'])
      mCamera.strafe(-0.01f);
   if (keys['s'])
      mCamera.move(-0.01f);
   if (keys['d'])
      mCamera.strafe(0.01f);
   glutPostRedisplay();
}

void DemoWindow::CallBackMouseFunc(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON)
   {
      mMouseLeft = (state == GLUT_DOWN);
   }
}

void DemoWindow::CallBackMotionFunc(int x, int y)
{
   mMouseDX = x - mPrevMouseX;
   mMouseDY = y - mPrevMouseY;
   mPrevMouseX = x, mPrevMouseY = y;
}

void DemoWindow::CallBackPassiveMotionFunc(int x, int y)
{
   mMouseDX = x - mPrevMouseX;
   mMouseDY = y - mPrevMouseY;
   mPrevMouseX = x, mPrevMouseY = y;
}

void DemoWindow::CallBackKeyboardUpFunc(unsigned char key, int x, int y)
{
   keys[key] = false;
}

void DemoWindow::switchRenderers()
{
   if (mRenderer == &mRayTracingRenderer)
      mRenderer = &mPreviewRenderer;
   else
      mRenderer = &mRayTracingRenderer;

   mRenderer->setupProjection(width, height, fovy);
}



