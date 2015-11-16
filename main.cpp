#include <iostream>
#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"
#include <unordered_map>

using namespace std;
using namespace Clustering;

int main() {
//    Point p1(5);
//    p1[2] = 3.14;
//    Point p2 = p1;
//    Point p2(5);
//    Point p3(5);
//    Point p4(5);
//    Point p5(5);
//
////    p2[1] = 3.14;
////    p1[0] = 5;
////    cout << (p1>=p2) << endl;
////    p1*=5;
////    p1+=p2;
//
//    p1[1] = 4;
//    p2[0] = 5;
//    p3[4] = 1;
//    p4[3] = 2;
//    p5[2] = 3;
//
//    Cluster c1;
//    Cluster c2;
////    Cluster c2(c1);
////    Cluster c3 = c1;
//
////    c3.computeCentroid();
//
//    c1.add(p1);
//    c1.add(p2);
//    c1.add(p3);
//    c2.add(p1);
//    c2.add(p2);
//    c2.add(p5);
//
//    cout << c1.validCentroid() << endl;
//    c1.computeCentroid();
//    cout << c1.validCentroid() << endl;

//    c1.remove(p5);
//    c1+=p5;
//    c2.add(c1.remove(p3));
//    c1+=c2; //Union
//    c1.remove(p2);

//    c1-=c2;
//    cout << interClusterDistance(c2,c1) << endl;
//    cout << c1.intraClusterDistance() << " " << c2.intraClusterDistance() << endl;
//    cout << c1.getClusterEdges() << " " << c2.getClusterEdges() << endl;
//    cout << interClusterEdges(c1,c2) << " " << interClusterEdges(c2, c1) << endl;

//    Point<double,3> p1;
//    Point<double,3> p2;
//    Point<double,3> p3;
//    Point<double,3> p4;
//    Point<double,3> p5;
//    p1[0] = 3.1;
//    p2[1] = 4.2;
//    p3[2] = 5.3;
//    p4[0] = 6.4;
//    p5[1] = 7.5;
//    Cluster<Point<double,3>,3> c1;


//    std::cout << "c1 contains p1: " << c1.contains(p1) << std::endl;
//    std::cout << "c1 contains p5: " << c1.contains(p5) << std::endl;

//    unsigned int key = whatIsKey(p1.getID(),p2.getID());
//    c1.intraClusterDistance();
//
//    Cluster<Point<double,3>,3> c2;

//    double newDist = p1.distanceTo(p2);
//    std::unordered_map<unsigned int,double> map;
//    std::pair<unsigned int,double> newEntry(key,newDist);
//    map.insert(newEntry);
//
//    cout << map.at(key) << " " << map.count(key);

//    Point<double,3> p1;
//    Point<double,4> p2;
//    Point<double,3> p3;
//    Point<double,3> p4;
//    Point<double,3> p5;
//    p1[2] = 3.1;
//    p2[1] = 4.2;
//    p3[2] = 5.3;
//    p4[0] = 6.4;
//    p5[1] = 7.5;

//    Cluster<Point<double,3>,3> c1;
//    c1.add(p1);
//    c1.add(p3);

//    cout << c1[-1] << endl;
//    cout << c1[3] << endl;
//    cout << p1[5];

//    c1.computeCentroid();
//    Cluster<Point<double,3>,3> c2;
//    c1.remove(p1);

//
//    cout << p1.distanceTo(p2)+p2.distanceTo(p3)+p1.distanceTo(p3) << endl;
//    cout << "c1 intraClusterDistance: " << c1.intraClusterDistance() << endl;
//    cout << "c1 intraClusterEdges: " << c1.getClusterEdges() << endl << endl;
//
//    cout << p1.distanceTo(p4)+p1.distanceTo(p5)+p2.distanceTo(p4)+p2.distanceTo(p5)+p3.distanceTo(p4)+p3.distanceTo(p5) << endl;
//    cout << "c1,c2 interClusterDistance: " << interClusterDistance(c1,c2) << endl;
//    cout << "c1,c2 interClusterEdges: " << interClusterEdges(c1,c2) << endl << endl;

//    KMeans<Point<double,3>,3,3> test;
    KMeans<Point<double,2>,10,2> test;

//    p1[5];
//    p1.getValue(8);

    return 0;
}