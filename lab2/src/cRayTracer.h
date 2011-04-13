#pragma once
#include <Eigen/Core>
#include "sMaterial.h"

class cRay;
class cScene;
class aWorldObject;

class cRayTracer
{
public:
   static const sMaterial::sMedium mAir, mGlass;
   static const double mThreshold;

   cRayTracer();
   void setScene(const cScene &scene)
   {
      mScene = &scene;
   }
   Eigen::Vector3f trace(const cRay &ray, const sMaterial::sMedium &curMed, double weight);
   virtual ~cRayTracer();
private:
   Eigen::Vector3f shade(const sMaterial::sMedium &curMed, double weight,
                         const Eigen::Vector3f &p, const Eigen::Vector3f &view, const aWorldObject *obj);

   const cScene *mScene;
   const int mMaxLevels;
   int mLevel;
   long mTotalRays;
};
