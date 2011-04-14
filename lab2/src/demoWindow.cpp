#define _USE_MATH_DEFINES
#include <cmath>

#include "demoWindow.h"
#include "cSphere.h"
#include "cPointLight.h"
#include "cSceneBuilder.h"

const static float fovy = (float)M_PI_4;

DemoWindow::DemoWindow(GlutMaster *glutMaster, int setWidth, int setHeight,
                       int setInitPositionX, int setInitPositionY, const char *title)
{
   mCurScene = 0;
   memset(mScenes, 0, 9 * sizeof(cScene*));
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

   //mScene.addLight(new cPointLight(Eigen::Vector3f(1, 1, 1),
   //      Eigen::Vector3f(10, 5, -10), 15));
   //mScene.addLight(new cPointLight(Eigen::Vector3f(0, 1, 0),
   //      Eigen::Vector3f(5, 10, 60), 15));

   //mScene.addObject(new cSphere(1.5f, mat,
   //      Eigen::Vector3f(0, 0, 50)));
   //mScene.addObject(new cSphere(1.5f, Eigen::Vector3f(0, 1, 0),
   //      Eigen::Vector3f(0, 10, 50)));
   //mScene.addObject(new cSphere(1.5f, Eigen::Vector3f(0, 0, 1),
   //      Eigen::Vector3f(-4, -4, 50)));
   //mScene.addObject(new cSphere(1.5f, Eigen::Vector3f(0, 1, 1),
   //      Eigen::Vector3f(-4, 10, 50)));

   //mScene.setBackground(0.3f, 0.3f, 0.3f);
   
   mState = PREVIEW;

   mScenes[0] = cSceneBuilder::scene1();
   mScenes[1] = cSceneBuilder::scene2();
   mScenes[2] = cSceneBuilder::scene3();
   //glutSetWindowTitle("Preview");
}

DemoWindow::~DemoWindow()
{
   glutDestroyWindow(windowID);
}

void DemoWindow::CallBackDisplayFunc(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   mRenderer->render(mCamera, *mScenes[mCurScene]);
   glutSetWindowTitle(mRenderer->titleInfo().c_str());

   glutSwapBuffers();
}

void DemoWindow::CallBackReshapeFunc(int w, int h)
{
   width = w;
   height = h;

   if (h == 0)
      h = 1;

   puts("Reshape");
   mRenderer->setupProjection(w, h, fovy);

   glutPostRedisplay();
}

void DemoWindow::CallBackKeyboardFunc(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 27: //ESC
      glutLeaveMainLoop();
      return;
   case 13: //ENTER
      switchRenderers();
      return;
   }

   if (mState == RAY_TRACER)
   {
      if (key == ' ')
      {
         mRayTracingRenderer.changeMode();
         glutPostRedisplay();
      }
      return;
   }

   if (key >= '1' && key <= '9')
   {
      if (mScenes[key - '1'])
         mCurScene = key - '1';
   }
   
   keys[key] = true;
}

void DemoWindow::CallBackIdleFunc(void)
{
   if (mState == RAY_TRACER)
      return;

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
   if (mState == RAY_TRACER)
      return;
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
   if (mState == RAY_TRACER)
      return;
   keys[key] = false;
}

void DemoWindow::switchRenderers()
{
   if (mState == RAY_TRACER)
      mRenderer = &mPreviewRenderer, mState = PREVIEW;
   else
      mRenderer = &mRayTracingRenderer, mState = RAY_TRACER;

   mRenderer->setupProjection(width, height, fovy);
}



