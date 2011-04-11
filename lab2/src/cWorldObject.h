#pragma once

#include "glut.h"
#include <Eigen/Core>
#include "iMaterialGenerator.h"

class cWorldObject
{
protected:
   Eigen::Vector3f mPos;
   const iMaterialGenerator &mMaterialGenerator;
public:
   cWorldObject() : mPos(0, 0, 0), mMaterialGenerator(*(new cMaterialSolid(Eigen::Vector3f(1, 0, 0)))) {};
   cWorldObject(const Eigen::Vector3f &color, 
                float x, float y, float z) : mPos(x, y, z),
                mMaterialGenerator(*(new cMaterialSolid(color)))
                {};
   cWorldObject(const Eigen::Vector3f &color, const Eigen::Vector3f &p) :
      mPos(p), mMaterialGenerator(*(new cMaterialSolid(color))) {};

   void setupWorld() {glTranslatef(mPos.x(), mPos.y(), mPos.z());}
   void setupMaterial() {glColor3fv(mMaterialGenerator.material(Eigen::Vector2f(0, 0)).mColor.data());}

   //sMaterial &material() {return mMaterial;}
   //const sMaterial &material() const {return mMaterial;}

   Eigen::Vector3f &position() {return mPos;}
   const Eigen::Vector3f &position() const {return mPos;}

   virtual ~cWorldObject() {};
};