#pragma once

class cFreeCamera;
class cScene;

class iRenderer
{
public:
   iRenderer() {};

   virtual void setupProjection(int width, int height, float fovy, float zNear, float zFar) = 0;
   virtual void render(const cFreeCamera &camera, const cScene &scene) = 0;

   virtual ~iRenderer() {};
};