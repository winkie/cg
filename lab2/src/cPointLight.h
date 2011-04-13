#pragma once

#include "iLight.h"

class cPointLight: public iLight
{
public:

   double DistScale;

   cPointLight(const Eigen::Vector3f &c, const Eigen::Vector3f &p, double d = 1.0): iLight(c, p), DistScale(d)
   {
   }

   virtual double Shadow(const cScene &scene, const Eigen::Vector3f &p, Eigen::Vector3f &l) const;
};
