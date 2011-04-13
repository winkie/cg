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
   cSphere(float radius, const Eigen::Vector3f &color) : mRadius(radius),
      aWorldObject(color, Eigen::Vector3f(0, 0, 0)) {};
   cSphere(float radius, const Eigen::Vector3f &color, 
      const Eigen::Vector3f &pos) : aWorldObject(color, pos), mRadius(radius) {};

   void render()
   {
      glPushMatrix();
      setupWorld();
      setupMaterial();
      glutSolidSphere(mRadius, 20, 20);
      glPopMatrix();
   }

   virtual std::pair<float, Eigen::Vector3f> intersect(const cRay &ray) const
   {
      Eigen::Vector3f pos = mPos - ray.orig;
      float t = pow(ray.dir.dot(pos), 2) - pos.dot(pos) + mRadius * mRadius;
      if (t < 0)
      {
         return std::make_pair(-1, Eigen::Vector3f());
      }
      else if (t < 1e-6)
      {
         float d = ray.dir.dot(pos);
         return std::make_pair(d, d * ray.dir + ray.orig);
      }
      else
      {
         float d = ray.dir.dot(pos);
         t = sqrt(t);
         if (d - t > 0)
            return std::make_pair(d - t, (d - t) * ray.dir + ray.orig);
         else if (d + t > 0)
            return std::make_pair(d + t, (d + t) * ray.dir + ray.orig);
         else
            return std::make_pair(-1, Eigen::Vector3f());
      }
   }
   virtual Eigen::Vector2f toSurfaceCoords(const Eigen::Vector3f &pos) const
   {
      return Eigen::Vector2f();
   }

   virtual ~cSphere() {};
};

