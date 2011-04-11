////////////////////////////////////////////////////////////////
//                                                            //
// demoWindow.h                                               //
// beta version 0.3 - 9/9/97)                                 //
//                                                            //
// George Stetten and Korin Crawford                          //
// copyright given to the public domain                       //
//                                                            //
// Please email comments to email@stetten.com                 //
//                                                            //
////////////////////////////////////////////////////////////////


#ifndef __DEMO_WINDOW_H__
#define __DEMO_WINDOW_H__

#include "glutMaster.h"
#include "cFreeCamera.h"

class DemoWindow : public GlutWindow{
private:
   cFreeCamera mCamera;
   bool mMouseLeft;
   int mMouseDX;
   int mPrevMouseX;
   int mPrevMouseY;
   int mMouseDY;
public:

   int          height, width;
   int          initPositionX, initPositionY;
   bool keys[256];

   DemoWindow(GlutMaster * glutMaster,
              int setWidth, int setHeight,
              int setInitPositionX, int setInitPositionY,
              char * title);
   ~DemoWindow();

   void CallBackDisplayFunc(void);
   void CallBackReshapeFunc(int w, int h);   
   void CallBackIdleFunc(void);
   void CallBackKeyboardFunc(unsigned char key, int x, int y);
   void CallBackKeyboardUpFunc(unsigned char key, int x, int y);
   void CallBackMouseFunc(int button, int state, int x, int y);
   void CallBackMotionFunc(int x, int y);
   void CallBackPassiveMotionFunc(int x, int y);
};

#endif
