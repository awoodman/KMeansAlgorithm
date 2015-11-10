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
    template <typename T, int dim>
    Cluster<T,dim>::Cluster(const Cluster<T,dim>& src): __centroid(0) {
        __centroid = src.__centroid;
        generateID();
        __size = src.__size;
        __dim = src.__dim;
        __valid_centroid = false;
        pointList = src.pointList;
    }

    template <typename T, int dim>
    Cluster<T,dim> &Cluster<T,dim>::operator=(const Cluster<T,dim>& src) {
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

    template <typename T, int dim>
    Cluster<T,dim>::~Cluster() {
        //TODO: What to destruct?
    }

    template <typename T, int dim>
    void Cluster<T,dim>::generateID() {
        static int id = 1;
        __id = id++;
    }

    template <typename T, int dim>
    T & Cluster<T,dim>::operator[](unsigned int index) {
        if (pointList.empty()) {
            cout << "The cluster is empty" << endl;
            //TODO: Return what here?
        }
        else {
            if (index < __size) {
                typename std::forward_list<T>::iterator it = pointList.begin();
                for (int i = 0; i < index; i++) {
                    it++;
                }
                return *it;
            }
        }
    }

    template <typename T, int dim>
    T Cluster<T,dim>::getPoint(unsigned int index) const {
        typename std::forward_list<T>::const_iterator it = pointList.begin();
        if (index == 0)
            return *it;
        else {
            for (int i = 0; i < index; i++) {
                it++;
            }
            return *it;
        }
    }

    template <typename T, int dim>
    void Cluster<T,dim>::setCentroid(const T & pt) {
        __centroid = pt;
        __valid_centroid = true;
    }

    template <typename T, int dim>
    void Cluster<T,dim>::invalidateCentroid() {
        __valid_centroid = false;
    }

    template <typename T, int dim>
    const T Cluster<T,dim>::getCentroid() {
        return __centroid;
    }

    template <typename T, int dim>
    void Cluster<T,dim>::computeCentroid() {
        T p(__dim);
        typename std::forward_list<T>::iterator it = pointList.begin();

        while (it != pointList.end())
        {
            p += *it/__size;
            it++;
        }

        this->setCentroid(p);
        __valid_centroid = true;
    }

    template <typename T, int dim>
    bool Cluster<T,dim>::validCentroid() {
        if (__valid_centroid)
            return true;
        else
            return false;
    }

    template <typename T, int dim>
    void Cluster<T,dim>::add(const T & newPoint) {
        __dim = newPoint.getDims();
        if (pointList.empty()) {
            pointList.push_front(newPoint);
        }
        else {
            bool add = false;
            int i = 0;
            typename std::forward_list<T>::iterator it = pointList.begin();
            typename std::forward_list<T>::iterator it_next = it;
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

    template <typename T, int dim>
    Cluster<T,dim> & Cluster<T,dim>::operator+=(const T &rhs) {
        this->add(rhs);
        return *this;
    }

    template <typename T, int dim>
    const T & Cluster<T,dim>::remove(const T & remPoint) {
        if (pointList.front() == remPoint) {
            pointList.pop_front();
            invalidateCentroid();
            __size--;
            return remPoint;
        }
        else {
            bool found = false;
            typename std::forward_list<T>::iterator it = pointList.begin();
            typename std::forward_list<T>::iterator it_next = pointList.begin();
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

    template <typename T, int dim>
    Cluster<T,dim> & Cluster<T,dim>::operator-=(const T &rhs) {
        this->remove(rhs);
        return *this;
    }

    template <typename T, int dim>
    Cluster<T,dim> & Cluster<T,dim>::operator+=(const Cluster<T,dim> &rhs) {
        if (rhs.__size == 0)
            return *this;
        else
        {
            bool add = true;
            int i = 0;
            typename std::forward_list<T>::const_iterator rhs_it = rhs.pointList.begin();
            while (i < rhs.__size)
            {
                add = true;
                int j = 0;
                typename std::forward_list<T>::iterator this_it = this->pointList.begin();
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

    template <typename T, int dim>
    Cluster<T,dim> & Cluster<T,dim>::operator-=(const Cluster<T,dim> &rhs) {
        if (rhs.__size == 0)
            return *this;
        else
        {
            bool keep = true;
            typename std::forward_list<T>::iterator this_it = this->pointList.begin();
            int i = 0;
            while (i < __size)
            {
                keep = true;
                typename std::forward_list<T>::const_iterator rhs_it = rhs.pointList.begin();
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

    template <typename S, int dim>
    bool operator==(const Cluster<S,dim> &lhs, const Cluster<S,dim> &rhs) {
        typename std::forward_list<S>::const_iterator lhs_it = lhs.pointList.begin();
        typename std::forward_list<S>::const_iterator rhs_it = rhs.pointList.begin();
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

    template <typename S, int dim>
    const Cluster<S,dim> operator+(const Cluster<S,dim> &lhs, const Cluster<S,dim> &rhs) {
        Cluster<S,dim> tempCluster(lhs);
        tempCluster+=rhs;
        return tempCluster;
    }

    template <typename S, int dim>
    const Cluster<S,dim> operator-(const Cluster<S,dim> &lhs, const Cluster<S,dim> &rhs) {
        Cluster<S,dim> tempCluster(lhs);
        tempCluster-=rhs;
        return tempCluster;
    }

    template <typename S, int dim>
    const Cluster<S,dim> operator+(const Cluster<S,dim> &lhs, const S &rhs) {
        Cluster<S,dim> tempCluster(lhs);
        tempCluster+=rhs;
        return tempCluster;
    }

    template <typename S, int dim>
    const Cluster<S,dim> operator-(const Cluster<S,dim> &lhs, const S &rhs) {
        Cluster<S,dim> tempCluster(lhs);
        tempCluster-=rhs;
        return tempCluster;
    }

    template <typename S, int dim>
    std::ostream &operator<<(std::ostream & os, Cluster<S,dim> & srcCluster) {
        typename std::forward_list<S>::iterator it = srcCluster.pointList.begin();
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

    template <typename S, int dim>
    std::istream &operator>>(std::istream & is, Cluster<S,dim> & destCluster) {
        string line;
        static const char DELIM = ',';

        while (getline(is,line)) {                                 // While '\n' not yet reached (takes in whole line)
            S* p = new S;
            stringstream lineStream(line);
            lineStream >> *p;
            destCluster.add(*p);
        }
    }

    template <typename T, int dim>
    void Cluster<T,dim>::pickPoints(int k, std::vector<T> & __initCent) {
        typename std::forward_list<T>::iterator it = this->pointList.begin();
        int increment = (this->__size)/k;

        // populate pointArray with 'k' points;
        for (int i = 0; i < k; i++)
        {
            __initCent.push_back(*it);
            for (int l = 0; l < increment; l++)
                it++;
        }
    }

    template <typename T, int dim>
    double Cluster<T,dim>::intraClusterDistance() const
    {
        typename std::forward_list<T>::const_iterator it1 = this->pointList.begin();
        typename std::forward_list<T>::const_iterator it2 = it1;
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

    template <typename S, int dim>
    double interClusterDistance(const Cluster<S,dim> &lhs, const Cluster<S,dim> &rhs) {
        typename std::forward_list<S>::const_iterator lhs_it = lhs.pointList.begin();
        typename std::forward_list<S>::const_iterator rhs_it = rhs.pointList.begin();
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

    template <typename T, int dim>
    int Cluster<T,dim>::getClusterEdges() {
        return __size*(__size-1)/2;
    }

    template <typename S, int dim>
    double interClusterEdges(const Cluster<S,dim> &c1, const Cluster<S,dim> &c2) {
        int edges = c1.__size*c2.__size;
        return edges;
    }

}
