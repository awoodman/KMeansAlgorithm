#include <iostream>

#include "Point.h"
#include "Cluster.h"

using namespace Clustering;

int main() {

//    Point p1(4);
//    Point p2(p1);
//    p1.setValue(1,3);
//    p2.setValue(0,3);
//
//    std::cout << p1 << std::endl << p2 << std::endl;
//
//    if (p1 == p2) {
//        std::cout << "Equal" << std::endl;
//    }
//
//    if (p1 != p2) {
//        std::cout << "Not Equal" << std::endl;
//    }
//
//    if (p1 > p2) {
//        std::cout << "Greater Than" << std::endl;
//    }
//
//    if (p1 < p2) {
//        std::cout << "Less Than" << std::endl;
//    }
//
//    if (p1 <= p2) {
//        std::cout << "Less Than or Equal" << std::endl;
//    }
//
//    if (p1 >= p2) {
//        std::cout << "Greater Than or Equal" << std::endl;
//    }
//
//    p1+=p2;
//
//    std::cout << p1;

    Point p1(4);
    Point p2(4);
    p1.setValue(1,2);
    p1.setValue(2,3);
    p2.setValue(0,4);
    p2.setValue(3,6);

    std::cout << p1;

    Cluster c1;

    return 0;
}