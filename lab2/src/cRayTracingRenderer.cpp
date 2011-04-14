#include "glut.h"
#include <iostream>
#include <Eigen/Geometry>

#include "cRayTracingRenderer.h"
#include "cFreeCamera.h"
#include "cRay.h"
#include "cScene.h"

static float Random(float l = 0, float r = 1)
{
   float s = (float)rand() / RAND_MAX;
   s = l + s * (r - l);
   return s;
}

cRayTracingRenderer::cRayTracingRenderer()
{
   mMode = DOF;
   mApertureSize = 0.5f;
   mFocalLength = 30.0f;
   puts("Cons");
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
   puts("Proj");
   mReRender = true;
}

void cRayTracingRenderer::render(const cFreeCamera &camera, const cScene &scene)
{
   if (mReRender)
   {
      printf("ReRendering\n");
      if (mMode == SIMPLE)
         traceRaysSimple(camera, scene);
      else if (mMode == DISTRIBUTED)
         traceRaysDistributed(camera, scene);
      else
         traceRaysDoF(camera, scene);
   }
   
   glRasterPos2i(0, mHeight - 1);
   glDrawPixels(mWidth, mHeight, GL_RGB, GL_FLOAT, &mBuffer[0]);
}

cRayTracingRenderer::~cRayTracingRenderer()
{
}

void cRayTracingRenderer::calcVectors( const cFreeCamera &camera )
{
   using namespace Eigen;

   mDir = camera.getDir();
   mDist = mHeight * 0.5f / tan(mFOVy * 0.5f);

   Vx = Vector3f(0, 1, 0).cross(mDir).normalized();
   Vy = mDir.cross(Vx).normalized();
   mEye = camera.getEye();
}

void cRayTracingRenderer::traceRaysSimple(const cFreeCamera &camera, const cScene &scene)
{
   calcVectors(camera);

   cRay ray;
   ray.orig = mEye;
   mRayTracer.setScene(scene);
   for (int j = 0; j < mHeight; ++j)
   {
      for (int i = 0; i < mWidth; ++i)
      {
         ray.dir = (mDir * mDist - 0.5f * (2 * i + 1 - mWidth) * Vx +
            0.5f * (2 * j + 1 - mHeight) * Vy).normalized();

         mBuffer[j * mWidth + i] = mRayTracer.trace(ray, cRayTracer::mAir, 1);
      }
   }
   mReRender = false;
}

void cRayTracingRenderer::traceRaysDoF(const cFreeCamera &camera, const cScene &scene)
{
   mReRender = false;
   calcVectors(camera);

   const int Ny = 7, Nx = 7;
   const float dW = 1.0f / Nx, dH = 1.0f / Ny;
   const float dWA = mApertureSize / Nx, dHA = mApertureSize / Ny;

   Eigen::Vector3f color(0, 0, 0), p, g;
   cRay ray;
   ray.orig = mEye;
   mRayTracer.setScene(scene);
   for (int j = 0; j < mHeight; ++j)
   {
      for (int i = 0; i < mWidth; ++i)
      {
         color = Eigen::Vector3f(0, 0, 0);
         p = (mDir * mDist - 
              (i + 0.5f - mWidth * 0.5f) * Vx +
              (j + 0.5f - mHeight * 0.5f) * Vy);
         float len = p.norm();
         p /= len;
         float len2 = len * (1 + mFocalLength / mDist);

         g = p * len;

         for (int l = 0; l < Ny; ++l)
         {
            for (int k = 0; k < Nx; ++k)
            {
               Eigen::Vector3f a = -
                  (Random(k * dWA, (k + 1) * dWA) - mApertureSize * 0.5f) * Vx +
                  (Random(l * dHA, (l + 1) * dHA) - mApertureSize * 0.5f) * Vy;
               ray.orig = mEye + a;
               ray.dir = (p * len2 - (g + a)).normalized();

               color += mRayTracer.trace(ray, cRayTracer::mAir, 1);
            }
         }
         mBuffer[j * mWidth + i] = color / (Nx * Ny);
      }
   }
}

void cRayTracingRenderer::traceRaysDistributed(const cFreeCamera &camera,
                                               const cScene &scene)
{
   mReRender = false;
   calcVectors(camera);

   const int Ny = 5, Nx = 5;
   const float dW = 1.0f / Nx, dH = 1.0f / Ny;

   Eigen::Vector3f color(0, 0, 0);
   cRay ray;
   ray.orig = mEye;
   mRayTracer.setScene(scene);
   for (int j = 0; j < mHeight; ++j)
   {
      for (int i = 0; i < mWidth; ++i)
      {
         color = Eigen::Vector3f(0, 0, 0);
         for (int l = 0; l < Ny; ++l)
         {
            for (int k = 0; k < Nx; ++k)
            {
               ray.dir = (mDir * mDist - 
                  (i + Random(k * dW, (k + 1) * dW) - mWidth * 0.5f) * Vx +
                  (j + Random(l * dH, (l + 1) * dH) - mHeight * 0.5f) * Vy).normalized();

               color += mRayTracer.trace(ray, cRayTracer::mAir, 1);
            }
         }
         mBuffer[j * mWidth + i] = color / (Nx * Ny);
      }
   }
}