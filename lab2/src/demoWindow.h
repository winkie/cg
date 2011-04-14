#ifndef __DEMO_WINDOW_H__
#define __DEMO_WINDOW_H__

#include "glutMaster.h"
#include "cFreeCamera.h"
#include "cPreviewRenderer.h"
#include "cScene.h"
#include "cRayTracingRenderer.h"

class DemoWindow: public GlutWindow
{
private:
   cPreviewRenderer mPreviewRenderer;
   cRayTracingRenderer mRayTracingRenderer;
   iRenderer *mRenderer;
   cFreeCamera mCamera;
   cScene *mScenes[9];
   int mCurScene;
   bool mMouseLeft;
   int mMouseDX;
   int mPrevMouseX;
   int mPrevMouseY;
   int mMouseDY;
   enum 
   {
      PREVIEW,
      RAY_TRACER
   } mState;
public:

   int height, width;
   int initPositionX, initPositionY;
   bool keys[256];

   DemoWindow(GlutMaster *glutMaster, int setWidth, int setHeight,
              int setInitPositionX, int setInitPositionY, const char *title);
   virtual ~DemoWindow();

   void CallBackDisplayFunc(void);
   void CallBackReshapeFunc(int w, int h);
   void CallBackIdleFunc(void);
   void CallBackKeyboardFunc(unsigned char key, int x, int y);
   void CallBackKeyboardUpFunc(unsigned char key, int x, int y);
   void CallBackMouseFunc(int button, int state, int x, int y);
   void CallBackMotionFunc(int x, int y);
   void CallBackPassiveMotionFunc(int x, int y);

private:
   void switchRenderers();
};

#endif
