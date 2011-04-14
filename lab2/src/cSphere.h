#pragma once

#include <cmath>
#include "glut.h"

#include "aWorldObject.h"
#include "cRay.h"

class cSphere: public aWorldObject
{
private:
   float mRadius;
   Eigen::Vector3f mPos;
public:
   cSphere(float radius, const Eigen::Vector3f &pos): mRadius(radius), mPos(pos) {};
   cSphere(float radius, const Eigen::Vector3f &pos,
      const sMaterial &mat) : aWorldObject(mat), mPos(pos), mRadius(radius) {};

   void render() const
   {
      glPushMatrix();
      glTranslatef((GLfloat)mPos.x(), (GLfloat)mPos.y(), (GLfloat)mPos.z());
      setupMaterial();
      glutSolidSphere(mRadius, 20, 20);
      glPopMatrix();
   }

   virtual float intersect(const cRay &ray) const
   {
      Eigen::Vector3f l = mPos - ray.orig;
      float L2OC = l.dot(l); // squared distance
      float tca = l.dot(ray.dir); // closest dist to center
      float t2hc = mRadius * mRadius - L2OC + tca * tca;
      float t2;
  
      if (t2hc <= 0.0)
         return -1;
  
      t2hc = sqrt(t2hc);
 
      float t;
      if (tca < t2hc) // we are inside
      {
         t = tca + t2hc;
         t2 = tca - t2hc;
      }
      else // we are outside
      {
         t = tca - t2hc;
         t2 = tca + t2hc;
      }
  
      if (fabs(t) < 0.001f) //GeomThreshold
         t = t2;
  
      if (t > 0.001f)
         return t;
      else
         return -1;
   }

   Eigen::Vector3f normal(const Eigen::Vector3f &p) const
   {
      Eigen::Vector3f t = p - mPos;
      return t / mRadius;
   }

   virtual ~cSphere() {};
};

