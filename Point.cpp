#include "Point.h"

// Default constructor
// Initializes the point to (0.0, 0.0)
Point::Point() {
  x = 0.0;
  y = 0.0;
  z = 0.0;
}

// Custom Constructor
// Initializes the point to (initX, initY)
Point::Point(double initX, double initY, double initZ) {
  x = initX;
  y = initY;
  z = initZ;
}


// Destructor
// No dynamic allocation, so nothing to do; if omitted, generated automatically
Point::~Point() {
  // no-op
}


// Mutator methods
// Change the values of private member variables

void Point::setX(double newX) {
  x = newX;
}

void Point::setY(double newY) {
  y = newY;
}

void Point::setZ(double newZ) {
  z = newZ;
}


// Accessors
// Return the current values of private member variables

double Point::getX() {
  return x;
}

double Point::getY() {
  return y;
}

double Point::getZ() {
  return z;
}


// Distance Calculator Function

double Point::distanceTo(Point &p) {
  double dist;
  dist = sqrt(pow((p.getX()-x),2)+pow((p.getY()-y),2)+pow((p.getZ()-z),2));      // sqrt((x2-x1)^2+(y2-y1)^2+(z2-z1)^2)
  return dist;
}
