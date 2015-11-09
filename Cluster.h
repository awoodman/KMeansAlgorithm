//
// Created by Adam on 11/4/2015.
//

#ifndef IP_PA4_CLUSTER_H
#define IP_PA4_CLUSTER_H

#include "Point.h"
#include <forward_list>

namespace Clustering {
    template <typename T, int dim>
    class Cluster {
    private:
        unsigned int __dim;
        unsigned int __id;
        unsigned int __size;
        bool __valid_centroid;
        Point<T,dim> __centroid;
        std::forward_list<Point<T,dim>> pointList;
    public:
        // Constructors
        Cluster() : __dim(dim), __size(0), __valid_centroid(false), __centroid(0) { generateID(); };

        // Big 3 (cpy const, assign op, destr)
        Cluster(const Cluster<T,dim>&);
        Cluster &operator=(const Cluster<T,dim>&);
        ~Cluster();

        // ID Gen
        void generateID();

        // Set Dimensions
        void setDimensionality(unsigned int userdim) { __dim = userdim; }

        // Get size
        unsigned int getSize() { return __size; }

        // Get ID
        unsigned int getID() const { return __id; }

        // Get specific Point
        Point<T,dim> &operator[](unsigned int);
        Point<T,dim> getPoint(unsigned int) const;

        // Centroid Operations
        void setCentroid(const Point<T,dim> &);
        void invalidateCentroid();
        const Point<T,dim> getCentroid();
        void computeCentroid();
        bool validCentroid();

        // Add and remove Points
        void add(const Point<T,dim> &);
        Cluster<T,dim> &operator+=(const Point<T,dim> &);
        const Point<T,dim> &remove(const Point<T,dim> &);
        Cluster<T,dim> &operator-=(const Point<T,dim> &rhs);

        // Union and Difference Clusters
        Cluster<T,dim> &operator+=(const Cluster<T,dim> &);
        Cluster<T,dim> &operator-=(const Cluster<T,dim> &);

        // Friend Functions
        template <typename S, int _dim>
        friend bool operator==(const Cluster<S,dim> &, const Cluster<S,dim> &);

        template <typename S, int _dim>
        friend const Cluster<S,dim> operator+(const Cluster<S,dim> &, const Cluster<S,dim> &);

        template <typename S, int _dim>
        friend const Cluster<S,dim> operator-(const Cluster<S,dim> &, const Cluster<S,dim> &);

        template <typename S, int _dim>
        friend const Cluster<S,dim> operator+(const Cluster<S,dim> &, const Point<S,dim> &);

        template <typename S, int _dim>
        friend const Cluster<S,dim> operator-(const Cluster<S,dim> &, const Point<S,dim> &);
        // I/O
        template <typename S, int _dim>
        friend std::ostream &operator<<(std::ostream &, Cluster<S,dim> &);

        template <typename S, int _dim>
        friend std::istream &operator>>(std::istream &, Cluster<S,dim> &);

        //Kmeans interaction
        void pickPoints(int k, std::vector<Point<T,dim>> &);

        // Cluster Distance Functions
        double intraClusterDistance() const;

        template <typename S, int _dim>
        friend double interClusterDistance(const Cluster<S,dim> &, const Cluster<S,dim> &);
        int getClusterEdges();

        template <typename S, int _dim>
        friend double interClusterEdges(const Cluster<S,dim> &, const Cluster<S,dim> &);

        class Move {
        private:
            Cluster<T,dim>* __from;
            Cluster<T,dim>* __to;
            Point<T,dim> __point;
        public:
            Move(const Point<T,dim> pt, Cluster<T,dim>* from_set, Cluster<T,dim>* to_set) : __point(0)
            {
                __point = pt;
                __from = from_set;
                __to = to_set;
            }
            void perform()
            {
                __to->add(__from->remove(__point));
            }
        };
    };
}

#include "Cluster.cpp"
#endif //IP_PA4_CLUSTER_H
