#include <Eigen/Geometry>
#include <iostream>

#include "cPreviewRenderer.h"
#include "cFreeCamera.h"
#include "cScene.h"
#include "cSphere.h"

cPreviewRenderer::cPreviewRenderer()
{
   // TODO Auto-generated constructor stub
}

void cPreviewRenderer::render(const cFreeCamera &camera, const cScene &scene)
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camera.setupMatrix();

   glBegin(GL_LINES);
   glColor3f(1, 0, 0);
   glVertex3f(0, 0, 0);
   glVertex3f(50, 0, 0);
   glColor3f(0, 1, 0);
   glVertex3f(0, 0, 0);
   glVertex3f(0, 50, 0);
   glColor3f(0, 0, 1);
   glVertex3f(0, 0, 0);
   glVertex3f(0, 0, 50);
   glEnd();

   for (cScene::tObjects::const_iterator it = scene.mObjects.begin();
         it != scene.mObjects.end(); ++it)
      ((iRenderable*)(*it))->render();
}

void cPreviewRenderer::setupProjection(int width, int height, float fovy, float zNear, float zFar)
{
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glEnable(GL_COLOR_MATERIAL);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glCullFace(GL_FRONT_AND_BACK);
   
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(fovy * 180.0f / M_PI, (GLfloat)width / (GLfloat)height, zNear, zFar);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

cPreviewRenderer::~cPreviewRenderer()
{
   // TODO Auto-generated destructor stub
}
