#pragma once

#include "iRenderer.h"

class cPreviewRenderer: public iRenderer
{
public:
   cPreviewRenderer();
   void setupProjection(int width, int height, float fovy, float zNear, float zFar);
   void render(const cFreeCamera &camera, const cScene &scene);
   virtual ~cPreviewRenderer();
};
