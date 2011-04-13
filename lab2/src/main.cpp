#include <iostream>

#include "glutMaster.h"
#include "glutWindow.h"
#include "demoWindow.h"

#include "cSphere.h"
#include "cRay.h"

GlutMaster *glutMaster;
DemoWindow *firstWindow = 0;
DemoWindow *secondWindow = 0;

int main(int argc, char **argv)
{
   glutMaster = new GlutMaster(argc, argv);

   firstWindow = new DemoWindow(glutMaster, 700, 700, // height, width
         300, 100, // initPosition (x,y)
         "First Window"); // title

   glutMaster->CallGlutMainLoop();

//   cSphere a(1.5f, Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(0, 10, 50));
//   cRay r(Eigen::Vector3f(0, 8.5, 50).normalized(), Eigen::Vector3f(0, 0, 0));
//
//   std::pair<bool, Eigen::Vector3f> i;
//   i = a.intersect(r);
//   std::cout << i.first << "\n" << i.second;

   return 0;
}
