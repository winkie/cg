#include "cScene.h"
#include "iLight.h"

cScene::cScene()
{

}

cScene::~cScene()
{
   for (tObjects::const_iterator it = mObjects.begin(); it != mObjects.end(); ++it)
      delete *it;
   for (tLights::const_iterator it = mLights.begin(); it != mLights.end(); ++it)
      delete *it;
}

void cScene::addObject(const aWorldObject *object)
{
   mObjects.push_back(object);
}

void cScene::addLight(const iLight *light)
{
   mLights.push_back(light);
}

std::pair<const aWorldObject*, float> cScene::intersect(const cRay &ray, float maxD) const
{
   float min = maxD;
   const aWorldObject *nearest = 0;
   for (cScene::tObjects::const_iterator it = mObjects.begin();
         it != mObjects.end(); ++it)
   {
      float d = (*it)->intersect(ray);

      if (d >= 0 && d < min)
      {
         min = d;
         nearest = (*it);
      }
   }
   return std::make_pair(nearest, min);
}
