#pragma once

#include "cWorldObject.h"
#include "iRenderable.h"

class cSphere: public cWorldObject, public iRenderable
{
private:
   float mRadius;
public:
   cSphere(float radius, const Eigen::Vector3f &color) : mRadius(radius),
      cWorldObject(color, Eigen::Vector3f(0, 0, 0)) {};
   cSphere(float radius, const Eigen::Vector3f &color, 
      const Eigen::Vector3f &pos) : cWorldObject(color, pos), mRadius(radius) {};

   void render()
   {
      glPushMatrix();
      setupWorld();
      setupMaterial();
      glutSolidSphere(mRadius, 20, 20);
      glPopMatrix();
   }

   ~cSphere() {};
};

