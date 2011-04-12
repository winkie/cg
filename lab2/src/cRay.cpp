#include "cRay.h"

cRay::cRay(): dir(0, 1, 0), orig(0, 0, 0)
{
}

cRay::~cRay()
{
   // TODO Auto-generated destructor stub
}

cRay::cRay(const Eigen::Vector3f &d): dir(d), orig(0, 0, 0)
{
}

cRay::cRay(const Eigen::Vector3f &d, const Eigen::Vector3f &o): dir(d), orig(o)
{
}


