#pragma once

#include "glut.h"
#include <Eigen/Core>

class cFreeCamera
{
public:
   cFreeCamera();
   ~cFreeCamera();

   void set(const Eigen::Vector3f &eye, const Eigen::Vector3f &at);

   const Eigen::Vector3f &getEye() const {return mEye;}
   void move(float dist);
   void strafe(float dist);
   void rotate(int mdx, int mdy);

   void setupMatrix()
   {
      Eigen::Vector3f at = mEye + mDir;
      gluLookAt(mEye.x(), mEye.y(), mEye.z(),
                at.x(), at.y(), at.z(),
                mUp.x(), mUp.y(), mUp.z());
   }

private:
   Eigen::Vector3f mEye, mDir, mUp;
};
