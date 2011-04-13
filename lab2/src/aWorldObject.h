#pragma once

#include "glut.h"
#include <Eigen/Core>
#include "iMaterialGenerator.h"

class cRay;

class aWorldObject
{
protected:
   Eigen::Vector3f mPos;
   const iMaterialGenerator &mMaterialGenerator;
public:
   aWorldObject() : mPos(0, 0, 0), mMaterialGenerator(*(new cMaterialSolid(Eigen::Vector3f(1, 0, 0)))) {};
   aWorldObject(const Eigen::Vector3f &color, 
                float x, float y, float z) : mPos(x, y, z),
                mMaterialGenerator(*(new cMaterialSolid(color)))
                {};
   aWorldObject(const Eigen::Vector3f &color, const Eigen::Vector3f &p) :
      mPos(p), mMaterialGenerator(*(new cMaterialSolid(color))) {};

   void setupWorld() {glTranslatef(mPos.x(), mPos.y(), mPos.z());}
   void setupMaterial() {glColor3fv(mMaterialGenerator.material(Eigen::Vector2f(0, 0)).mColor.data());}

   virtual std::pair<float, Eigen::Vector3f> intersect(const cRay &ray) const = 0;
   virtual Eigen::Vector2f toSurfaceCoords(const Eigen::Vector3f &pos) const = 0;
   virtual sMaterial getMaterialAt(const Eigen::Vector2f &pos) const
   {return mMaterialGenerator.material(pos);}

   //sMaterial &material() {return mMaterial;}
   //const sMaterial &material() const {return mMaterial;}

   Eigen::Vector3f &position() {return mPos;}
   const Eigen::Vector3f &position() const {return mPos;}

   virtual ~aWorldObject() {};
};
