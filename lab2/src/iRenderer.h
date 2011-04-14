#pragma once

#include <string>

class cFreeCamera;
class cScene;

class iRenderer
{
public:
   iRenderer() {};

   virtual void setupProjection(int width, int height, float fovy) = 0;
   virtual void render(const cFreeCamera &camera, const cScene &scene) = 0;
   virtual std::string titleInfo() = 0;

   virtual ~iRenderer() {};
};
