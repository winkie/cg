#pragma once 

#include <Eigen/Core>
#include "aWorldObject.h"

class cPlane: public aWorldObject
{
public:
	cPlane(const Eigen::Vector3f &n, float d);
   cPlane(const Eigen::Vector3f &n, float d, const sMaterial &mat);
   cPlane(float a, float b, float c, float d);
   cPlane(float a, float b, float c, float d, const sMaterial &mat);
   
   float intersect(const cRay& ray) const;
   Eigen::Vector3f normal(const Eigen::Vector3f& p) const
   {
      return mNormal;
   }
   void render() const;

	virtual ~cPlane();

private:
   Eigen::Vector3f mNormal;
   float mD;
};
