#include "cPointLight.h"
#include "cRayTracer.h"
#include "sMaterial.h"
#include "cRay.h"
#include "cScene.h"
#include "aWorldObject.h"

float cPointLight::Shadow(const cScene &scene, const Eigen::Vector3f &p, Eigen::Vector3f &l) const
{
   l = pos - p;

   float Dist = l.norm();
   float attenuation = DistScale / Dist;

   l /= Dist;

   cRay ray(l, p); // shadow ray
   sMaterial Texture;
   // check all occluding objects
   attenuation = attenuation * attenuation;// distance attenuation is prop. to squared dist.

   for (std::pair<const aWorldObject *, float> occlude = scene.intersect(ray, Dist);
         occlude.first && occlude.second < Dist;
         occlude = scene.intersect(ray, Dist))
   { 
      ray.orig = ray.point(occlude.second);
      Texture = occlude.first->getMaterialAt(ray.orig);

      if (Texture.mKTransp < cRayTracer::mThreshold) // object is opaque
         return 0;

      if ((attenuation *= Texture.mKTransp) < cRayTracer::mThreshold)
         return 0;

      Dist -= occlude.second;
   }

   return attenuation;
}
