// A 3-dimensional point class!
// Coordinates are double-precision floating point.

#ifndef __point_h
#define __point_h

#include <cmath>
#include <iostream>
#include <iomanip>

class Point {

private:
  double x;
  double y;
  double z;

public:
  // Constructors
  Point();                                   // default constructor
  Point(double x, double y, double z);       // three-argument constructor

  // Destructor
  ~Point();

  // Mutator methods
  void setX(double newX);
  void setY(double newY);
  void setZ(double newZ);

  // Accessor methods
  double getX();
  double getY();
  double getZ();

  // distance function
  double distanceTo(Point &p);      // takes in a reference to a point
};

#endif // __point_h