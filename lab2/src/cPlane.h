#pragma once 

#include <Eigen/Core>
#include "aWorldObject.h"

class cPlane: public aWorldObject
{
public:
	cPlane(const Eigen::Vector3f &n, double d);
   cPlane(double a, double b, double c, double d);
   cPlane(double a, double b, double c, double d, const sMaterial &mat);
   cPlane(const Eigen::Vector3f &n, double d, const sMaterial &mat);
   
   float intersect(const cRay& ray) const;
   Eigen::Vector3f normal(const Eigen::Vector3f& p) const
   {
      return mNormal;
   }
   void render() const;

	virtual ~cPlane();

private:
   Eigen::Vector3f mNormal;
   double mD;
};
