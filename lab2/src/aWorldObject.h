#pragma once

#include "glut.h"
#include <Eigen/Core>
#include "iMaterialGenerator.h"

class cRay;

class aWorldObject
{
protected:
   Eigen::Vector3f mPos;
public:
   sMaterial mDefMaterial;
   aWorldObject() : mPos(0, 0, 0) {};
   aWorldObject(float x, float y, float z) : mPos(x, y, z) {};
   aWorldObject(const Eigen::Vector3f &p) : mPos(p) {};
   aWorldObject(const sMaterial &mat,
      float x, float y, float z) : mPos(x, y, z), mDefMaterial(mat)
                {};
   aWorldObject(const sMaterial &mat, const Eigen::Vector3f &p) :
      mPos(p), mDefMaterial(mat) {};

   void setupWorld() {glTranslatef((GLfloat)mPos(0), (GLfloat)mPos(1), (GLfloat)mPos(2));}
   void setupMaterial() {glColor3fv(mDefMaterial.mColor.data());}

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

   Eigen::Vector3f &position() {return mPos;}
   const Eigen::Vector3f &position() const {return mPos;}

   virtual ~aWorldObject() {};
};
