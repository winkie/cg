#pragma once

#include <Eigen/Core>

class cRay
{
public:
   cRay();
   cRay(const Eigen::Vector3f &d);
   cRay(const Eigen::Vector3f &d, const Eigen::Vector3f &o);
   virtual ~cRay();
   Eigen::Vector3f dir;
   Eigen::Vector3f orig;
};
