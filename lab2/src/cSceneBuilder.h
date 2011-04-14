#pragma once

#include <Eigen/Core>

class cScene;

class cSceneBuilder
{
public:
   cSceneBuilder();
   virtual ~cSceneBuilder();
   cScene *getScene() {};
   void reset() {};
   void putSphere(const Eigen::Vector3f &pos, float radius) {};

   static cScene *scene1();
   static cScene *scene2();

private:
   cScene *mScene;
};
