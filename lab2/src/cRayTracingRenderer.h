#pragma once

#include <vector>

#include "iRenderer.h"
#include "cRayTracer.h"

class cRay;

class cRayTracingRenderer: public iRenderer
{
public:
   cRayTracingRenderer();

   void setupProjection(int width, int height, float fovy);
   void render(const cFreeCamera &camera, const cScene &scene);

   virtual ~cRayTracingRenderer();
private:
   int mWidth, mHeight;
   float mFOVy;
   bool mReRender;

   cRayTracer mRayTracer;
   void traceRays(const cFreeCamera &camera, const cScene &scene);
   std::vector<Eigen::Vector3f> mBuffer;
};
