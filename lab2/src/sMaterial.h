#pragma once

#include <Eigen/Core>

struct sMaterial
{
   struct sMedium
   {
      float mRefraction;
      float mBeta;
      sMedium(float r, float b) : mRefraction(r), mBeta(b) {};
   };

   float mKAmbi, mKDiff, mKSpec;
   float mKRefl, mKTransp;
   sMedium mMedium;
   int mP;
   Eigen::Vector3f mColor;
   Eigen::Vector3f mNormal;

   sMaterial(const Eigen::Vector3f &color = Eigen::Vector3f(0, 0, 1),
             float kAmbi = 0.2, float kDiff = 0.2, float kSpec = 0.2, double kRefl = 0,
             float kTransp = 0, float refraction = 1,
             float beta = 0, int p = 5)
      : mP(p), mColor(color), mKAmbi(kAmbi), mKDiff(kDiff), mKSpec(kSpec),
      mKRefl(kRefl), mKTransp(kTransp), mMedium(refraction, beta) {};
};
