#pragma once
#include <Eigen/Core>

class cRay;
class cScene;

class cRayTracer
{
public:
   cRayTracer();
   void setScene(const cScene &scene) {mScene = &scene;}
   Eigen::Vector3f trace(const cRay &ray) const;
   virtual ~cRayTracer();
private:
   const cScene *mScene;
};
