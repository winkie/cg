#include "cRayTracer.h"
#include "cScene.h"

cRayTracer::cRayTracer()
{

}

Eigen::Vector3f cRayTracer::trace(const cRay &ray) const
{
   float min = std::numeric_limits<float>::max();
   const aWorldObject *nearest = 0;
   for (cScene::tObjects::const_iterator it = mScene->mObjects.begin();
         it != mScene->mObjects.end(); ++it)
   {
      std::pair<float, Eigen::Vector3f> p = (*it)->intersect(ray);

      if (p.first >= 0 && p.first < min)
      {
         min = p.first;
         nearest = (*it);
      }
   }

   if (nearest)
      return nearest->getMaterialAt(Eigen::Vector2f(0, 0)).mColor;
   else
      return Eigen::Vector3f(0.1f, 0.1f, 0.1f);
}

cRayTracer::~cRayTracer()
{

}
