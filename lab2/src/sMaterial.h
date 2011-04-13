#pragma once

#include <Eigen/Core>

struct sMaterial
{
   struct sMedium
   {
      double mRefraction;
      double mBeta;
      sMedium(double r, double b) : mRefraction(r), mBeta(b) {};
   };

   double mKAmbi, mKDiff, mKSpec;
   double mKRefl, mKTransp;
   sMedium mMedium;
   int mP;
   Eigen::Vector3f mColor;
   Eigen::Vector3f mNormal;

   sMaterial(const Eigen::Vector3f &color = Eigen::Vector3f(0, 0, 1),
             double kAmbi = 0.2, double kDiff = 0.2, double kSpec = 0.2, double kRefl = 0,
             double kTransp = 0, double refraction = 1,
             double beta = 0, int p = 5)
      : mP(p), mColor(color), mKAmbi(kAmbi), mKDiff(kDiff), mKSpec(kSpec),
      mKRefl(kRefl), mKTransp(kTransp), mMedium(refraction, beta) {};
};
