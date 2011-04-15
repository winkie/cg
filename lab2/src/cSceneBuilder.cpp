#include "cRayTracer.h"
#include "cScene.h"
#include "cSphere.h"
#include "cPlane.h"
#include "cPointLight.h"
#include "cSceneBuilder.h"

cSceneBuilder::cSceneBuilder()
{
}

cSceneBuilder::~cSceneBuilder()
{
}

cScene* cSceneBuilder::scene1()
{
   cScene *scene = new cScene();
   
   cSphere *s[16];
   int i, j, k;
   for (i = k = 0; i < 4; i++)
   {
      for (j = 0; j < 4; j++, k++)
      {
         s[k] = new cSphere(0.7f, Eigen::Vector3f(-3 + j * 2.0f, 2.15f - i * 1.45f, 5.0f));

         if (i > 0)
            s[k]->mDefMaterial.mKAmbi = 0.2f;
         else
            s[k]->mDefMaterial.mKAmbi = j * 0.33f;

         if (i < 1)
            s[k]->mDefMaterial.mKDiff = 0;
         else if (i == 1)
            s[k]->mDefMaterial.mKDiff = j * 0.33f;
         else
            s[k]->mDefMaterial.mKDiff = 0.4f;

         if (i < 2)
            s[k]->mDefMaterial.mKSpec = 0;
         else if (i == 2)
            s[k]->mDefMaterial.mKSpec = j * 0.33f;
         else
            s[k]->mDefMaterial.mKSpec = 0.7f;

         if (i < 3)
            s[k]->mDefMaterial.mP = 10;
         else
            s[k]->mDefMaterial.mP = 5 + 5 * j;

         s[k]->mDefMaterial.mKTransp = 0;
         s[k]->mDefMaterial.mKRefl = 0;
         s[k]->mDefMaterial.mColor = Eigen::Vector3f(0, 1, 0);
         s[k]->mDefMaterial.mMedium.mRefraction = 1;
         s[k]->mDefMaterial.mMedium.mBeta = 0;
         scene->addObject(s[k]);
      }
   }

   scene->addLight(new cPointLight(Eigen::Vector3f(1, 1, 1),
         Eigen::Vector3f(10, 5, -10), 15));
         
   scene->setBackground(0.3f, 0.3f, 0.3f);
   return scene;
}


cScene* cSceneBuilder::scene2()
{
   cScene *scene = new cScene();

   sMaterial sphereMat;
   sphereMat.mKAmbi = 0.2f;
   sphereMat.mKDiff = 0.5f;
   sphereMat.mKSpec = 0.6f;
   sphereMat.mKRefl = 0;
   sphereMat.mKTransp = 0;
   sphereMat.mP = 30;
   sphereMat.mColor = Eigen::Vector3f(1, 1, 0);
   sphereMat.mMedium = cRayTracer::mGlass;
   
   cSphere *s1, *s2, *s3;
   
   s1 = new cSphere(1.5, Eigen::Vector3f(0, 1, 5), sphereMat);
   s1->mDefMaterial.mKRefl = 0.3f;
   
   s2 = new cSphere(1, Eigen::Vector3f(-3, 0, 4), sphereMat);
   s2->mDefMaterial.mColor = Eigen::Vector3f(1, 0, 0);
   
   s3 = new cSphere(1, Eigen::Vector3f(3, 0, 4), sMaterial(
      Eigen::Vector3f(1, 1, 1),
      0, 0, 0, 0, 1, 1.5f, 0, 30));

   scene->addObject(s1);
   scene->addObject(s2);
   scene->addObject(s3);

   sMaterial planeMat;
   planeMat.mKAmbi = 0.1f;
   planeMat.mKSpec = 0.4f;
   planeMat.mKDiff = 0.5f;
   planeMat.mKRefl = 0.4f;
   planeMat.mMedium = cRayTracer::mGlass;
   scene->addObject(new cPlane(Eigen::Vector3f(0, 1, 0), 1, planeMat));
   
   scene->addLight(new cPointLight(Eigen::Vector3f(1, 1, 1),
         Eigen::Vector3f(10, 5, -10), 17));
         
   scene->setBackground(0.3f, 0.3f, 0.3f);
   
   return scene;
}

cScene * cSceneBuilder::scene3()
{
   cScene *scene = new cScene();

   sMaterial sphereMat;
   sphereMat.mKAmbi = 0.2f;
   sphereMat.mKDiff = 0.5f;
   sphereMat.mKSpec = 0.4f;
   sphereMat.mKRefl = 0.5f;
   sphereMat.mKTransp = 0;
   sphereMat.mP = 30;
   sphereMat.mColor = Eigen::Vector3f(1, 1, 0);
   sphereMat.mMedium = cRayTracer::mGlass;

   for (int i = 0; i < 10; i++)
   {
      sphereMat.mColor = Eigen::Vector3f(i * 0.1f, i * 0.03f + 0.3f, i * 0.04f + 0.5f);
      scene->addObject(new cSphere(1.5f, Eigen::Vector3f(0, 1, i * 7.0f + 5), sphereMat));
   }

   sMaterial planeMat;
   planeMat.mKAmbi = 0.1f;
   planeMat.mKSpec = 0.4f;
   planeMat.mKDiff = 0.5f;
   //planeMat.mKRefl = 0.4f;
   planeMat.mColor = Eigen::Vector3f(0.3f, 0.7f, 0.2f);
   planeMat.mMedium = cRayTracer::mGlass;
   scene->addObject(new cCheckersPlane(Eigen::Vector3f(0, 1, 0), 1, planeMat));

   planeMat.mColor = Eigen::Vector3f(0.5f, 0.1f, 0.4f);
   scene->addObject(new cCheckersPlane(Eigen::Vector3f(0, 0, -1), 300, planeMat));

   scene->addLight(new cPointLight(Eigen::Vector3f(1, 1, 1),
      Eigen::Vector3f(10, 1, 7), 17));

   scene->addLight(new cPointLight(Eigen::Vector3f(1, 1, 1),
      Eigen::Vector3f(10, 1, 47), 17));

   return scene;
}
