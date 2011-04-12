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
   const Eigen::Vector3f &getDir() const {return mDir;}
   void move(float dist);
   void strafe(float dist);
   void rotate(int mdx, int mdy);

   void setupMatrix() const
   {
      Eigen::Vector3f cntr = mEye + mDir;
      gluLookAt(mEye.x(), mEye.y(), mEye.z(),
                cntr.x(), cntr.y(), cntr.z(),
                mUp.x(), mUp.y(), mUp.z());
   }

private:
   Eigen::Vector3f mEye, mDir, mUp;
};
