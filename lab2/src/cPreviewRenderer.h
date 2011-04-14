#pragma once

#include "iRenderer.h"

class cPreviewRenderer: public iRenderer
{
public:
   cPreviewRenderer();
   void setupProjection(int width, int height, float fovy);
   void render(const cFreeCamera &camera, const cScene &scene);
   std::string titleInfo()
   {
      return "Preview";
   }
   virtual ~cPreviewRenderer();
};
