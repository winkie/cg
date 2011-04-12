#include <Eigen/Geometry>
#include <cmath>

#include "cFreeCamera.h"

cFreeCamera::cFreeCamera() : mUp(0.0f, 1.0f, 0.0f)
{
}

cFreeCamera::~cFreeCamera()
{
}

void cFreeCamera::set(const Eigen::Vector3f &eye, const Eigen::Vector3f &at)
{
   mEye = eye;
   mDir = at - eye;
   mDir.normalize();
}

void cFreeCamera::rotate(int mdx, int mdy)
{
   float dx = mdx * 0.003f;
   float dy = mdy * 0.003f;
   Eigen::Vector3f cross = mDir.cross(mUp);
   Eigen::AngleAxisf t(Eigen::AngleAxisf(dy, cross.normalized()));

   Eigen::Vector3f newDir = t * mDir, newUp;
   
   if (fabs(newDir.dot(mUp)) < 0.998)
      mDir = newDir;

   newUp = t * mUp;
   t = Eigen::AngleAxisf(dx, newUp.normalized());
   
   mDir = t * mDir;
}

void cFreeCamera::move(float dist)
{
   Eigen::Vector3f shift = dist * mDir;
   mEye += shift;
}

void cFreeCamera::strafe(float dist)
{
   Eigen::Vector3f cross;
   cross = mDir.cross(mUp);
   cross.normalize();
   cross *= dist;
   mEye += cross;
}
