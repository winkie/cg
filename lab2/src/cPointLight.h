#pragma once

#include "iLight.h"

class cPointLight: public iLight
{
public:
   float DistScale;

   cPointLight(const Eigen::Vector3f &c, const Eigen::Vector3f &p, float d = 1.0f): iLight(c, p), DistScale(d)
   {
   }

   virtual float Shadow(const cScene &scene, const Eigen::Vector3f &p, Eigen::Vector3f &l) const;
};
