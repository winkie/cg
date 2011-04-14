#include "cRayTracer.h"
#include "cScene.h"
#include "iLight.h"

using namespace Eigen;

const sMaterial::sMedium cRayTracer::mAir(1, 0);
const sMaterial::sMedium cRayTracer::mGlass(1.5, 0);
const double cRayTracer::mThreshold = 0.01;

cRayTracer::cRayTracer(): mMaxLevels(10), mTotalRays(0), mLevel(0)
{

}

Eigen::Vector3f cRayTracer::trace(const cRay &ray, const sMaterial::sMedium &curMed, double weight)
{
   Vector3f color(0, 0, 0);
   mLevel++;
   mTotalRays++;
   std::pair<const aWorldObject *, float> p = mScene->intersect(ray, std::numeric_limits<float>::max());

   if (p.first)
   {
      color = shade(curMed, weight, ray.point(p.second), ray.dir, p.first);

      if (curMed.mBeta > mThreshold)
         color *= exp(-p.second * curMed.mBeta);
   }
   else
      color = mScene->mBackground;

   mLevel--;
   return color;
}

cRayTracer::~cRayTracer()
{

}

Eigen::Vector3f cRayTracer::shade(const sMaterial::sMedium &curMed, double weight,
                                  const Eigen::Vector3f &p, const Eigen::Vector3f &view,
                                  const aWorldObject *obj)
{
   sMaterial txt;
   cRay ray;
   Vector3f color(0, 0, 0), l, h;
   float Sh;
   float ln, vn;

   int Entering = 1;

   txt = obj->getMaterialAt(p);

   if ((vn = view.dot(txt.mNormal)) > 0)
   {
      txt.mNormal = -txt.mNormal;
      vn = -vn;
      Entering = 0;
   }

   ray.orig = p;
   color = txt.mColor * txt.mKAmbi; // * Ambient ?

   for (cScene::tLights::const_iterator light = mScene->mLights.begin();
         light != mScene->mLights.end(); ++light)
   {
      if ((Sh = (*light)->Shadow(*mScene, p, l)) > mThreshold)
      {
         if ((ln = l.dot(txt.mNormal)) > mThreshold)
         {
            if (txt.mKDiff > mThreshold)
            {
               Vector3f t((*light)->color);
               t(0) *= txt.mColor(0); t(1) *= txt.mColor(1); t(2) *= txt.mColor(2);
               color += t * txt.mKDiff * Sh * ln;
            }

            if (txt.mKSpec > mThreshold)
            {
               h = (l - view).normalized();
               color += (*light)->color * txt.mKSpec * Sh * pow(txt.mNormal.dot(h), txt.mP);
            }
         }
      }
   }

   double rWeight = weight * txt.mKRefl;
   double tWeight = weight * txt.mKTransp;

   if (rWeight > mThreshold && mLevel < mMaxLevels)
   {
      ray.dir = view - txt.mNormal * (2 * vn);
      color += txt.mKRefl * trace(ray, curMed, rWeight);
   }

   if (tWeight > mThreshold && mLevel < mMaxLevels)
   {
      float Eta = curMed.mRefraction / (Entering?txt.mMedium.mRefraction:mAir.mRefraction);
      float ci = -vn;
      float ctSq = 1 + Eta * Eta * (ci * ci - 1);
      if (ctSq > mThreshold)
      {
         ray.dir = view * Eta + txt.mNormal * (Eta * ci - sqrt(ctSq));
         if (Entering)
            color += txt.mKRefl * trace(ray, txt.mMedium, tWeight);
         else
            color += txt.mKRefl * trace(ray, mAir, tWeight);
      }
   }

   return color;
}




