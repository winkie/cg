#pragma once

#include <Eigen/Core>

class cScene;

class iLight
{
public:
   Eigen::Vector3f color;
   Eigen::Vector3f pos;
   iLight(const Eigen::Vector3f &c, const Eigen::Vector3f &p): color(c), pos(p) {};
   virtual ~iLight() {};

   virtual float Shadow(const cScene &scene, const Eigen::Vector3f &p, Eigen::Vector3f &l) const = 0;
};
