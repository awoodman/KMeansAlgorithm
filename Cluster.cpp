//
// Created by Adam on 11/4/2015.
//

#include "Cluster.h"
#include <fstream>
#include <sstream>

// iostream
using std::cout;
using std::endl;

// fstream
using std::ifstream;

// sstream
using std::stringstream;
using std::string;

namespace Clustering {
    Cluster::Cluster(const Cluster& src): __centroid(0) {
        __centroid = src.__centroid;
        generateID();
        __size = src.__size;
        __dim = src.__dim;
        __valid_centroid = false;
        pointList = src.pointList;
    }

    Cluster &Cluster::operator=(const Cluster& src) {
        pointList.clear();
        if (this->__id != src.__id) {
            __size = src.__size;
            __dim = src.__dim;
            __valid_centroid = false;
            if (!(src.pointList.empty()))
                pointList = src.pointList;
            else
                cout << "The source cluster is empty" << endl;
        }
    }

    Cluster::~Cluster() {
        //TODO: What to destruct?
    }

    void Cluster::generateID() {
        static int id = 1;
        __id = id++;
    }

    Point & Cluster::operator[](unsigned int index) {
        if (pointList.empty()) {
            cout << "The cluster is empty" << endl;
            //TODO: Return what here?
        }
        else {
            if (index < __size) {
                std::forward_list<Point>::iterator it = pointList.begin();
                for (int i = 0; i < index; i++) {
                    it++;
                }
                return *it;
            }
        }
    }

    Point Cluster::getPoint(unsigned int index) const {
        std::forward_list<Point>::const_iterator it = pointList.begin();
        if (index == 0)
            return *it;
        else {
            for (int i = 0; i < index; i++) {
                it++;
            }
            return *it;
        }
    }

    void Cluster::setCentroid(const Point & pt) {
        __centroid = pt;
        __valid_centroid = true;
    }

    void Cluster::invalidateCentroid() {
        __valid_centroid = false;
    }

    const Point Cluster::getCentroid() {
        return __centroid;
    }

    void Cluster::computeCentroid() {
        Point p(__dim);
        std::forward_list<Point>::iterator it = pointList.begin();

        while (it != pointList.end())
        {
            p += *it/__size;
            it++;
        }

        this->setCentroid(p);
        __valid_centroid = true;
    }

    bool Cluster::validCentroid() {
        if (__valid_centroid)
            return true;
        else
            return false;
    }

    void Cluster::add(const Point & newPoint) {
        __dim = newPoint.getDims();
        if (pointList.empty()) {
            pointList.push_front(newPoint);
        }
        else {
            bool add = false;
            int i = 0;
            std::forward_list<Point>::iterator it = pointList.begin();
            std::forward_list<Point>::iterator it_next = it;
            it_next++;
            if (newPoint <= *it) {
                pointList.push_front(newPoint);
                add = true;
            }
            else if (__size == 1) {
                pointList.insert_after(it, newPoint);
                add = true;
            }
            else {
                while ((it_next != pointList.end()) && !(add)) {
                    if (newPoint <= *it_next) {
                        pointList.insert_after(it,newPoint);
                        add = true;
                    }
                    else {
                        it++;
                        it_next++;
                        add = false;
                    }
                    i++;
                }
            }
            if (!(add)) {
                pointList.insert_after(it,newPoint);
            }
        }
        __size++;
        this->invalidateCentroid();
    }

    Cluster & Cluster::operator+=(const Point &rhs) {
        this->add(rhs);
        return *this;
    }

    const Point & Cluster::remove(const Point & remPoint) {
        if (pointList.front() == remPoint) {
            pointList.pop_front();
            invalidateCentroid();
            __size--;
            return remPoint;
        }
        else {
            bool found = false;
            std::forward_list<Point>::iterator it = pointList.begin();
            std::forward_list<Point>::iterator it_next = pointList.begin();
            it_next++;
            int i = 0;
            while (*it_next != remPoint && (it_next != pointList.end())) {
                it++;
                it_next++;
                i++;
            }
            if (*it_next == remPoint) {
                found = true;
                pointList.erase_after(it);
            }
            if (found) {
                __size--;
                this->invalidateCentroid();
                return remPoint;
            }
            else
                cout << "The point was not found in this cluster" << endl;
        }
    }

    Cluster & Cluster::operator-=(const Point &rhs) {
        this->remove(rhs);
        return *this;
    }

    Cluster & Cluster::operator+=(const Cluster &rhs) {
        if (rhs.__size == 0)
            return *this;
        else
        {
            bool add = true;
            int i = 0;
            std::forward_list<Point>::const_iterator rhs_it = rhs.pointList.begin();
            while (i < rhs.__size)
            {
                add = true;
                int j = 0;
                std::forward_list<Point>::iterator this_it = this->pointList.begin();
                while ((j < __size) && add)
                {
                    if (*this_it == *rhs_it) {
                        add = false;
                    }
                    else {
                        add = true;
                    }
                    this_it++;
                    j++;
                }
                if (add)
                {
                    this->add(*rhs_it);
                }
                rhs_it++;
                i++;
            }
        }
        __valid_centroid = false;       // Invalidate Centroid
        return *this;
    }

    Cluster & Cluster::operator-=(const Cluster &rhs) {
        if (rhs.__size == 0)
            return *this;
        else
        {
            bool keep = true;
            std::forward_list<Point>::iterator this_it = this->pointList.begin();
            int i = 0;
            while (i < __size)
            {
                keep = true;
                std::forward_list<Point>::const_iterator rhs_it = rhs.pointList.begin();
                int j = 0;
                while ((j < rhs.__size) && keep)
                {
                    if (*rhs_it == *this_it)
                    {
                        keep = false;
                    }
                    rhs_it++;
                    j++;
                }
                if (!(keep))
                {
                    this->remove(*this_it);
                }
                if (keep)
                    this_it++;
                i++;
            }
        }

        this->__valid_centroid = false;       // Invalidate Centroid
        return *this;
    }

    bool operator==(const Cluster &lhs, const Cluster &rhs) {
        std::forward_list<Point>::const_iterator lhs_it = lhs.pointList.begin();
        std::forward_list<Point>::const_iterator rhs_it = rhs.pointList.begin();
        int i = 0, j = 0;
        bool decision = true;

        //3 Potential Cases
        if (lhs.__size != rhs.__size) {                         // If cluster sizes aren't the same
            return false;
        }
        else if ((lhs.__size == 0) && (rhs.__size == 0))            // If both clusters have 0
        {
            return true;
        }
        else {                                                  // If sizes are greater than 0
            while ((i < lhs.__size) && (j < rhs.__size))
            {
                if (*lhs_it == *rhs_it)
                {
                    decision = true;
                    rhs_it++;
                    lhs_it++;
                    i++;
                    j++;
                }
                else
                    return false;
            }
            return decision;
        }
    }

    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {
        Cluster tempCluster(lhs);
        tempCluster+=rhs;
        return tempCluster;
    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {
        Cluster tempCluster(lhs);
        tempCluster-=rhs;
        return tempCluster;
    }

    const Cluster operator+(const Cluster &lhs, const Point &rhs) {
        Cluster tempCluster(lhs);
        tempCluster+=rhs;
        return tempCluster;
    }

    const Cluster operator-(const Cluster &lhs, const Point &rhs) {
        Cluster tempCluster(lhs);
        tempCluster-=rhs;
        return tempCluster;
    }

    std::ostream &operator<<(std::ostream & os, Cluster & srcCluster) {
        std::forward_list<Point>::iterator it = srcCluster.pointList.begin();
        int i = 0;
        while (i < srcCluster.__size)
        {
            os << *it;
            os << srcCluster.getID() << endl;
            it++;
            i++;
        }
        return os;
    }

    std::istream &operator>>(std::istream & is, Cluster & destCluster) {
        string line;
        static const char DELIM = ',';

        while (getline(is,line)) {                                 // While '\n' not yet reached (takes in whole line)
            Point* p = new Point(destCluster.__dim);
            stringstream lineStream(line);
            lineStream >> *p;
            destCluster.add(*p);
        }
    }

    void Cluster::pickPoints(int k, std::vector<Point> & __initCent) {
        std::forward_list<Point>::iterator it = this->pointList.begin();
        int increment = (this->__size)/k;

        // populate pointArray with 'k' points;
        for (int i = 0; i < k; i++)
        {
            __initCent.push_back(*it);
            for (int l = 0; l < increment; l++)
                it++;
        }
    }

    double Cluster::intraClusterDistance() const
    {
        std::forward_list<Point>::const_iterator it1 = this->pointList.begin();
        std::forward_list<Point>::const_iterator it2 = it1;
        int i = 0, j = 0;
        double totalDist = 0;

        while (i < __size) {
            while (j < __size) {
                if (*it1 != *it2) {
                    totalDist = totalDist + it1->distanceTo(*it2);
                }
                it2++;
                j++;
            }
            it2 = this->pointList.begin();
            j = 0;
            it1++;
            i++;
        }

        return totalDist/2.0;
    }

    double interClusterDistance(const Cluster &lhs, const Cluster &rhs) {
        std::forward_list<Point>::const_iterator lhs_it = lhs.pointList.begin();
        std::forward_list<Point>::const_iterator rhs_it = rhs.pointList.begin();
        int i = 0, j = 0;

        double totalDist = 0;
        while (i < lhs.__size) {
            while (j < rhs.__size) {
                if (lhs_it != rhs_it) {
                    totalDist = totalDist + lhs_it->distanceTo(*rhs_it);
                }
                rhs_it++;
                j++;
            }
            lhs_it++;
            i++;
        }

        return totalDist;
    }

    int Cluster::getClusterEdges() {
        return __size*(__size-1)/2;
    }

    double interClusterEdges(const Cluster &c1, const Cluster &c2) {
        int edges = c1.__size*c2.__size;
        return edges;
    }

}
