#pragma once

#include "glut.h"
#include <Eigen/Core>
#include "iMaterialGenerator.h"

class cRay;

class aWorldObject
{
public:
   sMaterial mDefMaterial;
   aWorldObject() {};
   aWorldObject(const sMaterial &mat): mDefMaterial(mat) {};

   void setupMaterial() const {glColor3fv(mDefMaterial.mColor.data());}
   virtual void render() const {};

   virtual float intersect(const cRay &ray) const = 0;

   virtual Eigen::Vector3f normal(const Eigen::Vector3f &p) const = 0;

   sMaterial getMaterialAt(const Eigen::Vector3f &p) const
   {
      sMaterial mat = mDefMaterial;
      mat.mNormal = normal(p);
      return mat;
   }

   //sMaterial &material() {return mMaterial;}
   //const sMaterial &material() const {return mMaterial;}

   virtual ~aWorldObject() {};
};
