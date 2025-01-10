#include "exceptions.h"
#include <cmath>
#include <iostream>
#include <vector>
// Greed refinement
// Total number od divisions for Bezier curve
#define CELL 100
int fact(uint n)
{
  return (n == 0) || (n == 1) ? 1 : n * fact(n - 1);
}
double Ni(uint n, uint i)
{
  if (i > n)
  {
    throw "Couldn't compute Ni coefficient. i > n";
  }
  return fact(n) / (fact(i) * fact(n - i));
}

double basisFunc(uint n, uint i, double t)
{
  return Ni(n, i) * pow(t, i) * pow(1 - t, n - i);
}

/*Compute the value of Bernstein polynimial*/
double Bernstein(int index, int degree, double paramT)
{
  if (index < 0 || index > degree)
  {
    return 0.0;
  }
  if (index == 0 || index == degree)
  {
    return 1.0;
  }

  VALIDATE_ARGUMENT(degree >= 0, "degree", "Degree must be greater than or equal zero.");
  VALIDATE_ARGUMENT_RANGE(paramT, 0.0, 1.0);

  std::vector<double> temp(degree + 1, 0.0);
  temp[degree - index] = 1.0;
  for (int k = 0; k <= degree; k++)
  {
    for (int j = degree; j >= k; j--)
    {
      temp[j] = (1.0 - paramT) * temp[j] + paramT * temp[j - 1];
    }
  }
  return temp[degree];
}

std::vector<double> AllBernstein(int degree, double paramT)
{
  VALIDATE_ARGUMENT(degree > 0, "degree", "Degree must be greater than zero.");
  VALIDATE_ARGUMENT_RANGE(paramT, 0.0, 1.0);
  std::vector<double> bernsteinArray(degree + 1);
  bernsteinArray[0] = 1.0;

  double t1 = 1.0 - paramT;
  for (int j = 1; j <= degree; j++)
  {
    double saved = 0.0;
    for (int k = 0; k < j; k++)
    {
      double temp = bernsteinArray[k];
      bernsteinArray[k] = saved + t1 * temp;
      saved = paramT * temp;
    }
    bernsteinArray[j] = saved;
  }
  return bernsteinArray;
}
int main(int args, char** argv)
{
  // Create three points
  double origin[3] = { 0.0, 0.0, 0.0 };
  double p1[3] = { 1.0, 0.0, 0.0 };
  double p2[3] = { 0.0, 1.0, 0.0 };
  double p3[3] = { 0.0, 0.0, 1.0 };

  //   // Number of Control Points
  //   uint nCPTS = 3;
  //   // Total number of segments
  //   uint n = nCPTS - 1;
  int n = 3;
  double u = 0.1;
  std::vector<double> result = AllBernstein(n, u);
  for (size_t i = 0; i < result.size(); i++)
  {
    printf("B_%ld_%d(%.1f) = %f\n", i, n, u, result[i]);
  }
}