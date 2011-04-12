#pragma once

#include <vector>
#include "cSphere.h"

class cScene
{
public:
   cScene();
   virtual ~cScene();
   void addObject(const cSphere *object);

   typedef std::vector<const cSphere*> tObjects;
   tObjects mObjects;

   //void addLight();

   typedef std::vector<int /*Lights*/> tLights;
   tLights mLights;
};
