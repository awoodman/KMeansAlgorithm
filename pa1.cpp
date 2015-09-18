//
// Created by Ivo Georgiev on 8/25/15.
//

#include "Point.h"
using namespace std;

//double computeArea(Point &, Point &, Point &);  // function prototype for computeArea

int main() {

    Point p1(3);
    Point p2(3);

    p1.setCoord(1,2.5);
    p1.setCoord(2,3.5);
    p1.setCoord(3,4.5);

    p2.setCoord(1,5.5);
    p2.setCoord(2,6.5);
    p2.setCoord(3,7.5);

    double dist = p1.distanceTo(p2);
    cout << "Distance between points is: " << showpoint << fixed << setprecision(2) << dist;

    return 0;

}


//double computeArea(Point &p1, Point &p2, Point &p3)     // Parameters point1,point2,point3
//{
//    double s, area;
//    double side1, side2, side3;             // Side lengths side1,side2,side3
//
//    side1 = p1.distanceTo(p2);              // call distanceTo function to find side length 1
//    side2 = p2.distanceTo(p3);              // call distanceTo function to find side length 2
//    side3 = p3.distanceTo(p1);              // call distanceTo function to find side length 3
//
//    s = (side1 + side2 + side3) / 2;        // Calculate Triangle Perimeter
//
//    area = sqrt(s*(s-side1)*(s-side2)*(s-side3));    // Calculate area
//
//    return area;
//}