#include "glut.h"
#include <iostream>
#include <Eigen/Geometry>

#include "cRayTracingRenderer.h"
#include "cFreeCamera.h"
#include "cRay.h"
#include "cScene.h"

cRayTracingRenderer::cRayTracingRenderer()
{
   mReRender = true;
}

void cRayTracingRenderer::setupProjection(int width, int height, float fovy)
{
   mWidth = width, mHeight = height, mFOVy = fovy;
   glDisable(GL_DEPTH_TEST);

   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, width, height, 0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   mBuffer.resize(width * height);
   mReRender = true;
}

void cRayTracingRenderer::render(const cFreeCamera &camera, const cScene &scene)
{
   if (mReRender)
      traceRays(camera, scene);
   
   glRasterPos2i(0, mHeight - 1);
   glDrawPixels(mWidth, mHeight, GL_RGB, GL_FLOAT, &mBuffer[0]);
}

cRayTracingRenderer::~cRayTracingRenderer()
{
}

void cRayTracingRenderer::traceRays(const cFreeCamera &camera, const cScene &scene)
{
   using namespace Eigen;

   Vector3f dir = camera.getDir();
   Vector3f Vx, Vy;
   float d = mHeight * 0.5f / tan(mFOVy * 0.5f);

   Vx = Vector3f(0, 1, 0).cross(dir).normalized();
   Vy = dir.cross(Vx).normalized();

   cRay ray;
   ray.orig = camera.getEye();

   mRayTracer.setScene(scene);
   for (int j = 0; j < mHeight; ++j)
   {
      for (int i = 0; i < mWidth; ++i)
      {
         ray.dir = (dir * d - 0.5f * (2 * i + 1 - mWidth) * Vx + 0.5f * (2 * j + 1 - mHeight) * Vy).normalized();

         mBuffer[j * mWidth + i] = mRayTracer.trace(ray, cRayTracer::mAir, 1);
      }
   }
   mReRender = false;
}


