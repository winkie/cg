#pragma once

#include <cmath>

#include "aWorldObject.h"
#include "iRenderable.h"
#include "cRay.h"

class cSphere: public aWorldObject, public iRenderable
{
private:
   float mRadius;
public:
   cSphere(float radius, const Eigen::Vector3f &pos): mRadius(radius),
      aWorldObject(pos) {};
   cSphere(float radius, const Eigen::Vector3f &pos,
      const sMaterial &mat) : aWorldObject(mat, pos), mRadius(radius) {};

   void render()
   {
      glPushMatrix();
      setupWorld();
      setupMaterial();
      glutSolidSphere(mRadius, 20, 20);
      glPopMatrix();
   }

   virtual float intersect(const cRay &ray) const
   {
      Eigen::Vector3f pos = mPos - ray.orig;
      float t = pow(ray.dir.dot(pos), 2) - pos.dot(pos) + mRadius * mRadius;
      if (t < 0)
      {
         return -1;
      }
      else if (t < 1e-6)
      {
         float d = ray.dir.dot(pos);
         return d;
      }
      else
      {
         float d = ray.dir.dot(pos);
         t = sqrt(t);
         if (d - t > 0)
            return d - t;
         else if (d + t > 0)
            return d + t;
         else
            return -1;
      }
   }

   Eigen::Vector3f normal(const Eigen::Vector3f &p) const
   {
      Eigen::Vector3f t = p - mPos;
      return t / mRadius;
   }

   virtual ~cSphere() {};
};

