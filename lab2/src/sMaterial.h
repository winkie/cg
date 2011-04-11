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

   sMaterial(const Eigen::Vector3f &color, double kAmbi = 0, double kDiff = 0,
      double kRefl = 0, double kTransp = 0, double refraction = 0,
      double beta = 0, int p = 0)
      : mP(p), mColor(color), mKAmbi(kAmbi), mKDiff(kDiff),
      mKRefl(kRefl), mKTransp(kTransp), mMedium(refraction, beta) {};
};