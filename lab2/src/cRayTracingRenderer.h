#pragma once

#include <vector>

#include "iRenderer.h"

class cRay;

class cRayTracingRenderer: public iRenderer
{
public:
   cRayTracingRenderer();

   void setupProjection(int width, int height, float fovy, float zNear, float zFar);
   void render(const cFreeCamera &camera, const cScene &scene);

   virtual ~cRayTracingRenderer();
private:
   int mWidth, mHeight;
   float mFovy;
   Eigen::Vector3f mTopLeft, mTopRight, mBottomLeft, mBottomRight;
   bool mReRender;

   void renderRays(const cFreeCamera &camera, const cScene &scene);
   std::vector<Eigen::Vector3f> mBuffer;
   Eigen::Vector3f trace(const cRay &ray, const cScene &scene);
};
