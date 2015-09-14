//
// Created by Ivo Georgiev on 8/25/15.
//

#include "Point.h"
using namespace std;

double computeArea(Point &, Point &, Point &);  // function prototype for computeArea

int main(void) {
    double xin, yin, zin;                       // Temporary point coordinates
    Point a, b, c;                              // Points a,b,c

    cout << "Please enter x-coordinate of Point 1: ";
    cin >> xin;                                 // point a x-coord
    cout << "Please enter y-coordinate of Point 1: ";
    cin >> yin;                                 // point a y-coord
    cout << "Please enter z-coordinate of Point 1: ";
    cin >> zin;                                 // point a z-coord

    a.setX(xin);                                // set a x-coord
    a.setY(yin);                                // set a y-coord
    a.setZ(zin);                                // set a z-coord

    cout << "Please enter x-coordinate of Point 2: ";
    cin >> xin;                                 // point b x-coord
    cout << "Please enter y-coordinate of Point 2: ";
    cin >> yin;                                 // point b y-coord
    cout << "Please enter z-coordinate of Point 2: ";
    cin >> zin;                                 // point b z-coord

    b.setX(xin);                                // set b x-coord
    b.setY(yin);                                // set b y-coord
    b.setZ(zin);                                // set b z-coord

    cout << "Please enter x-coordinate of Point 3: ";
    cin >> xin;                                 // point c x-coord
    cout << "Please enter y-coordinate of Point 3: ";
    cin >> yin;                                 // point c y-coord
    cout << "Please enter z-coordinate of Point 3: ";
    cin >> zin;                                 // point c z-coord

    c.setX(xin);                                // set c x-coord
    c.setY(yin);                                // set c y-coord
    c.setZ(zin);                                // set c z-coord

    cout << "The area of the triangle is: " << showpoint << setprecision(2) << fixed << computeArea(a,b,c) << endl;    // Output

    return 0;
}


double computeArea(Point &p1, Point &p2, Point &p3)     // Parameters point1,point2,point3
{
    double s, area;
    double side1, side2, side3;             // Side lengths side1,side2,side3

    side1 = p1.distanceTo(p2);              // call distanceTo function to find side length 1
    side2 = p2.distanceTo(p3);              // call distanceTo function to find side length 2
    side3 = p3.distanceTo(p1);              // call distanceTo function to find side length 3

    s = (side1 + side2 + side3) / 2;        // Calculate Triangle Perimeter

    area = sqrt(s*(s-side1)*(s-side2)*(s-side3));    // Calculate area

    return area;
}