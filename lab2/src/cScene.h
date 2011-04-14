#pragma once

#include <vector>
#include <Eigen/Core>
#include "cSphere.h"

class iLight;

class cScene
{
public:
   cScene();
   virtual ~cScene();

   Eigen::Vector3f mBackground;
   void setBackground(float r, float g, float b)
   {
      mBackground = Eigen::Vector3f(r, g, b);
   }

   void addObject(const aWorldObject *object);
   typedef std::vector<const aWorldObject*> tObjects;
   tObjects mObjects;

   void addLight(const iLight *light);
   typedef std::vector<const iLight*> tLights;
   tLights mLights;

   std::pair<const aWorldObject *, float> intersect(const cRay &ray, float maxD) const;
};
