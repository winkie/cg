#pragma once

#include <Eigen/Core>
#include "sMaterial.h"

class iMaterialGenerator
{
public:
   iMaterialGenerator() {};
   virtual ~iMaterialGenerator() {};
   virtual sMaterial material(const Eigen::Vector2f &pos) const = 0;
};

class cMaterialSolid: public iMaterialGenerator
{
private:
   sMaterial mMaterial;
public:
   cMaterialSolid(const Eigen::Vector3f &color): mMaterial(color) {};
   sMaterial material(const Eigen::Vector2f &pos) const
   {
      return mMaterial;
   }
   virtual ~cMaterialSolid() {};
};
