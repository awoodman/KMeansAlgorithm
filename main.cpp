#include <iostream>

#include "Point.h"
#include "Cluster.h"
// TESTING THE PUSH COMMAND WITH TAGS (THIS SHOULD CHANGE PA3_1.0)
using namespace Clustering;

int main() {

    Point p1(4);
    Point p2(p1);
    p1.setValue(1,3);
    p2.setValue(0,3);

    std::cout << p1 << std::endl << p2 << std::endl;

    if (p1 == p2) {
        std::cout << "Equal" << std::endl;
    }

    if (p1 != p2) {
        std::cout << "Not Equal" << std::endl;
    }

    if (p1 > p2) {
        std::cout << "Greater Than" << std::endl;
    }

    if (p1 < p2) {
        std::cout << "Less Than" << std::endl;
    }

    if (p1 <= p2) {
        std::cout << "Less Than or Equal" << std::endl;
    }

    if (p1 >= p2) {
        std::cout << "Greater Than or Equal" << std::endl;
    }

    p1+=p2;

    std::cout << p1 << std::endl;

    Point p3(4);
    p1.setValue(1,2);
    p1.setValue(2,3);
    p2.setValue(0,4);
    p2.setValue(3,6);
    p3.setValue(0,3.1415);
    Point p4(4);
    p4.setValue(1,8.642);

    std::cout << p1 << std::endl << p2 << std::endl << p3 << std::endl << p4 << std::endl;

    Cluster c1;
    c1.add(&p1);

    Cluster c2;
    c2.add(&p2);

    if (c1 == c2)
        std::cout << "They're Equal" << std::endl;
    else
        std::cout << "They're NOT Equal" << std::endl;

    Cluster c3(c1);

    PointPtr Point2 = &p2;
    c3.add(Point2);
    PointPtr Point3 = &p3;

    c3 = c3 + Point3;

    c3+=p4;

    c3-=p3;

    c2 = c3 + Point3;

    c2 = c2 - Point2;
    c1.add(&p3);

    Cluster c5 = c1 - c3;

    c5+=c3;

    c5-=c3;

    return 0;
}