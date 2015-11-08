//
// Created by Adam on 11/4/2015.
//

#ifndef IP_PA4_CLUSTER_H
#define IP_PA4_CLUSTER_H

#include "Point.h"
#include <forward_list>

namespace Clustering {
    class Cluster {
    private:
        unsigned int __dim;
        unsigned int __id;
        unsigned int __size;
        bool __valid_centroid;
        Point __centroid;
        std::forward_list<Point> pointList;
    public:
        // Constructors
        Cluster() : __dim(0), __size(0), __valid_centroid(false), __centroid(0) { generateID(); };

        // Big 3 (cpy const, assign op, destr)
        Cluster(const Cluster&);
        Cluster &operator=(const Cluster&);
        ~Cluster();

        // ID Gen
        void generateID();

        // Set Dimensions
        void setDimensionality(unsigned int dim) { __dim = dim; }

        // Get size
        unsigned int getSize() { return __size; }

        // Get ID
        unsigned int getID() const { return __id; }

        // Get specific Point
        Point &operator[](unsigned int);

        Point getPoint(unsigned int) const;

        // Centroid Operations
        void setCentroid(const Point &);
        void invalidateCentroid();
        const Point getCentroid();
        void computeCentroid();
        bool validCentroid();

        // Add and remove Points
        void add(const Point &);
        Cluster &operator+=(const Point &);
        const Point &remove(const Point &);
        Cluster &operator-=(const Point &rhs);

        // Union and Difference Clusters
        Cluster &operator+=(const Cluster &);
        Cluster &operator-=(const Cluster &);

        // Friend Functions
        friend bool operator==(const Cluster &, const Cluster &);
        friend const Cluster operator+(const Cluster &, const Cluster &);
        friend const Cluster operator-(const Cluster &, const Cluster &);
        friend const Cluster operator+(const Cluster &, const Point &);
        friend const Cluster operator-(const Cluster &, const Point &);
        // I/O
        friend std::ostream &operator<<(std::ostream &, Cluster &);
        friend std::istream &operator>>(std::istream &, Cluster &);

        //Kmeans interaction
        void pickPoints(int k, std::vector<Point> &);

        // Cluster Distance Functions
        double intraClusterDistance() const;
        friend double interClusterDistance(const Cluster &, const Cluster &);
        int getClusterEdges();
        friend double interClusterEdges(const Cluster &, const Cluster &);

        class Move {
        private:
            Cluster* __from;
            Cluster* __to;
            Point __point;
        public:
            Move(const Point pt, Cluster * from_set, Cluster * to_set) : __point(0)
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
