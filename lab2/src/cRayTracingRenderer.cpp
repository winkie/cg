#include "glut.h"
#include <iostream>
#include <Eigen/Geometry>

#include "cRayTracingRenderer.h"
#include "cFreeCamera.h"
#include "cRay.h"
#include "cScene.h"

cRayTracingRenderer::cRayTracingRenderer()
{
   mReRender = true;
}

void cRayTracingRenderer::setupProjection(int width, int height, float fovy, float zNear, float zFar)
{
   mWidth = width, mHeight = height;

   mFovy = fovy; //mZNear = zNear;

   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, width, height, 0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   mBuffer.resize(width * height);
   mReRender = true;
}

void cRayTracingRenderer::render(const cFreeCamera &camera, const cScene &scene)
{
//   glBegin(GL_LINES);
//   glColor3f(1, 0, 0);
//   glVertex2i(0, 0);
//   glColor3f(0, 1, 0);
//   glVertex2i(mWidth, mHeight);
//   glColor3f(0, 0, 1);
//   glVertex2i(0, mHeight);
//   glColor3f(0, 1, 0);
//   glVertex2i(mWidth, 0);
//   glEnd();
//   return;
   if (mReRender)
      renderRays(camera, scene);

   glBegin(GL_POINTS);
   for (int j = 0; j < mHeight; ++j)
   {
      for (int i = 0; i < mWidth; ++i)
      {
         glColor3fv(mBuffer[j * mWidth + i].data());
         glVertex2i(i, j);
      }
   }
   glEnd();
}

cRayTracingRenderer::~cRayTracingRenderer()
{
   // TODO Auto-generated destructor stub
}

void cRayTracingRenderer::renderRays(const cFreeCamera &camera, const cScene &scene)
{
   using namespace Eigen;
   Vector3f l, r;
   Vector3f topLeft, topRight, bottomLeft, bottomRight;
   Vector3f dir = camera.getDir();

   float aspect = (float)mWidth / mHeight;
   using namespace Eigen;
   Vector3f c = camera.getDir().normalized(); //(0, 0, 1);
   Vector3f R = Vector3f(0, 1, 0).cross(c).normalized();//(1, 0, 0);
   Vector3f top, bottom;
   Affine3f t;
   float a = -mFovy * 0.5f;
   t = AngleAxisf(a, R);
   top = t * c;
   t = AngleAxisf(-a, R);
   bottom = t * c;

   a *= -aspect;
   t = AngleAxisf(a, top.cross(R).normalized());
   mTopLeft = t * top;
   t = AngleAxisf(-a, top.cross(R).normalized());
   mTopRight = t * top;

   t = AngleAxisf(a, bottom.cross(R).normalized());
   mBottomLeft = t * bottom;
   t = AngleAxisf(-a, bottom.cross(R).normalized());
   mBottomRight = t * bottom;

   mTopLeft.normalize();
   mTopRight.normalize();
   mBottomLeft.normalize();
   mBottomRight.normalize();

   std::cout << mTopLeft << "\n\n";
   std::cout << mTopRight << "\n\n";
   std::cout << mBottomLeft << "\n\n";
   std::cout << mBottomRight << "\n\n";

   //float angle;
   //Affine3f t;
   //angle = acos(dir.dot(Vector3f(0, 0, 1)) / dir.norm());
   //t = AngleAxisf(angle, dir.cross(Vector3f(0, 0, 1)));

   topLeft = mTopLeft;
   topRight = mTopRight;
   bottomLeft = mBottomLeft;
   bottomRight = mBottomRight;

   cRay ray;
   ray.orig = camera.getEye();

   for (int j = 0; j < mHeight; ++j)
   {
      float y = (j + 0.5f) / mHeight;
      l = (1 - y) * topLeft + y * bottomLeft;
      r = (1 - y) * topRight + y * bottomRight;

      for (int i = 0; i < mWidth; ++i)
      {
         float x = (i + 0.5f) / mWidth;
         ray.dir = ((1 - x) * l + x * r).normalized();
         //ray.dir = (camera.getDir() + Vector3f(i - mWidth * 0.5f, j - mHeight * 0.5f, 500).normalized()).normalized();

         Vector3f c;
         mBuffer[j * mWidth + i] = trace(ray, scene);
      }
   }
   mReRender = false;
}

Eigen::Vector3f cRayTracingRenderer::trace(const cRay &ray, const cScene &scene)
{
   for (cScene::tObjects::const_iterator it = scene.mObjects.begin();
            it != scene.mObjects.end(); ++it)
   {
      std::pair<bool, Eigen::Vector3f> p = (*it)->intersect(ray);
      if (p.first)
         return (*it)->getMaterialAt(Eigen::Vector2f(0, 0)).mColor;
   }
   return Eigen::Vector3f(0.1f, 0.1f, 0.1f);
}


