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
   void changeMode()
   {
      if (mMode == SIMPLE)
         mMode = DISTRIBUTED;
      else if (mMode == DISTRIBUTED)
         mMode = DOF;
      else
         mMode = SIMPLE;

      puts("Switch");
      mReRender = true;
   }

   std::string titleInfo()
   {
      std::string s = "Tracer.";
      if (mMode == SIMPLE)
         s += " Simple mode.";
      else if (mMode == DOF)
      {
         s += " DoF mode. Aperture size = ";
         std::ostringstream oss;
         oss << mApertureSize;
         s += oss.str();
      }
      else
         s += " Distributed mode.";


      return s;
   }

   virtual ~cRayTracingRenderer();
   bool mReRender;
private:
   int mWidth, mHeight;
   float mFOVy;
   float mApertureSize;
   float mFocalLength;
   Eigen::Vector3f mDir, mEye, Vx, Vy;
   float mDist;

   void calcVectors(const cFreeCamera &camera);

   enum
   {
      SIMPLE,
      DISTRIBUTED,
      DOF
   } mMode;

   cRayTracer mRayTracer;
   void traceRaysSimple(const cFreeCamera &camera, const cScene &scene);
   void traceRaysDoF(const cFreeCamera &camera, const cScene &scene);
   void traceRaysDistributed(const cFreeCamera &camera, const cScene &scene);
   std::vector<Eigen::Vector3f> mBuffer;
};
