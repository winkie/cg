#include "cPointLight.h"
#include "cRayTracer.h"
#include "sMaterial.h"
#include "cRay.h"
#include "cScene.h"
#include "aWorldObject.h"

double cPointLight::Shadow(const cScene &scene, const Eigen::Vector3f &p, Eigen::Vector3f &l) const
{
   l = pos - p;

   double Dist = l.norm(); // distance to light source
   double attenuation = DistScale / Dist; // distance attenuation of light

   l /= Dist; // Normalize vector l

   cRay ray(l, p); // shadow ray
   sMaterial Texture;
   // check all occluding objects
   attenuation = attenuation * attenuation;// distance attenuation is prop. to squared dist.

   for (std::pair<const aWorldObject *, float> occlude = scene.intersect(ray, Dist);
         occlude.first && occlude.second < Dist;
         occlude = scene.intersect(ray, Dist))
   { // adjust ray origin and get transparency coefficient
      if (occlude.second < cRayTracer::mThreshold) //TODO:Shit right there
         break;
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
