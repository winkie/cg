#pragma once

class iRenderable
{
public:
   iRenderable(void) {};
   virtual void render() = 0;
   ~iRenderable(void) {};
};

