#include "cScene.h"

cScene::cScene()
{

}

cScene::~cScene()
{
   for (tObjects::const_iterator it = mObjects.begin(); it != mObjects.end(); ++it)
      delete *it;
}

void cScene::addObject(const cSphere *object)
{
   mObjects.push_back(object);
}


