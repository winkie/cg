#include <Eigen/Geometry>

#include "cRayTracer.h"
#include "cRay.h"
#include "cPlane.h"

cPlane::cPlane(const Eigen::Vector3f& n, double d): mNormal(n.normalized()), mD(d)
{
}

cPlane::cPlane(const Eigen::Vector3f& n, double d, const sMaterial& mat): mNormal(n.normalized()), mD(d), aWorldObject(mat)
{
}

cPlane::cPlane(double a, double b, double c, double d)
{
   mNormal = Eigen::Vector3f(a, b, c);
   double norm = mNormal.norm();
   
   mNormal /= norm;
   mD = d / norm;
}

cPlane::cPlane(double a, double b, double c, double d, const sMaterial& mat): aWorldObject(mat)
{
   mNormal = Eigen::Vector3f(a, b, c);
   double norm = mNormal.norm();
   
   mNormal /= norm;
   mD = d / norm;
}

cPlane::~cPlane()
{
   
}

float cPlane::intersect(const cRay &ray) const
{
   const float vd = mNormal.dot(ray.dir);
   const float EPS = 1e-6;
   if (vd > -EPS && vd < EPS)
      return -1;
  
   float t = -(mNormal.dot(ray.orig) + mD) / vd;
  
   if (t > cRayTracer::mThreshold)
      return t;
   else
      return -1;
}

void cPlane::render() const
{
   glPushMatrix();
   Eigen::Vector3f mPos = -mNormal * mD;
   Eigen::Vector3f eX, eY;
   if (mD > 1e-6)
   {
      Eigen::Vector3f v(10, 10, 10);
      int i = -1;
      float m = 0;
      if (mNormal.x() > 1e-6)
         i = 0;
      else if (mNormal.y() > 1e-6)
         i = 1;
      else if (mNormal.z() > 1e-6)
         i = 2;
         
      m = mNormal(i), v(i) = 0;
      m = (mD + v.dot(mNormal)) / m;
      v(i) = m;
      eX = v;
   }
   else
   {
      eX = Eigen::Vector3f(0, 0, 1);
   }
      
   eX = (eX + mPos).normalized();
   eY = mNormal.cross(eX).normalized();

   const int W = 50;
   const int H = 50;
   glTranslatef((GLfloat)mPos.x(), (GLfloat)mPos.y(), (GLfloat)mPos.z());
   setupMaterial();
   
   //glutSolidSphere(0.01, 20, 20);
   glBegin(GL_QUADS);
   glVertex3fv(Eigen::Vector3f(-W * eX - H * eY).data());
   glVertex3fv(Eigen::Vector3f(-W * eX + H * eY).data());
   glVertex3fv(Eigen::Vector3f(W * eX + H * eY).data());
   glVertex3fv(Eigen::Vector3f(W * eX - H * eY).data());
   glEnd();
   
   glPopMatrix();
}

