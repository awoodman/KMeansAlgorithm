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
        int __dim;
        unsigned int __id;
        unsigned int __size;
        bool __valid_centroid;
        T __centroid;
        std::forward_list<T> pointList;
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
        T &operator[](unsigned int);
        T getPoint(unsigned int) const;

        // Centroid Operations
        void setCentroid(const T &);
        void invalidateCentroid();
        const T getCentroid();
        void computeCentroid();
        bool validCentroid();

        // Add and remove Points
        void add(const T &);
        Cluster<T,dim> &operator+=(const T &);
        const T &remove(const T &);
        Cluster<T,dim> &operator-=(const T &rhs);

        // Union and Difference Clusters
        Cluster<T,dim> &operator+=(const Cluster<T,dim> &);
        Cluster<T,dim> &operator-=(const Cluster<T,dim> &);

        // Friend Functions
        template <typename S, int _dim>
        friend bool operator==(const Cluster<S,_dim> &, const Cluster<S,_dim> &);

        template <typename S, int _dim>
        friend const Cluster<S,_dim> operator+(const Cluster<S,_dim> &, const Cluster<S,_dim> &);

        template <typename S, int _dim>
        friend const Cluster<S,_dim> operator-(const Cluster<S,_dim> &, const Cluster<S,_dim> &);

        template <typename S, int _dim>
        friend const Cluster<S,_dim> operator+(const Cluster<S,_dim> &, const S &);

        template <typename S, int _dim>
        friend const Cluster<S,_dim> operator-(const Cluster<S,_dim> &, const S &);
        // I/O
        template <typename S, int _dim>
        friend std::ostream &operator<<(std::ostream &, Cluster<S,_dim> &);

        template <typename S, int _dim>
        friend std::istream &operator>>(std::istream &, Cluster<S,_dim> &);

        //Kmeans interaction
        void pickPoints(int k, std::vector<T> &);

        // Cluster Distance Functions
        double intraClusterDistance() const;

        template <typename S, int _dim>
        friend double interClusterDistance(const Cluster<S,_dim> &, const Cluster<S,_dim> &);
        int getClusterEdges();

        template <typename S, int _dim>
        friend double interClusterEdges(const Cluster<S,_dim> &, const Cluster<S,_dim> &);

        class Move {
        private:
            Cluster<T,dim>* __from;
            Cluster<T,dim>* __to;
            T __point;
        public:
            Move(const T pt, Cluster<T,dim>* from_set, Cluster<T,dim>* to_set) : __point(0)
            {
                __point = pt;
                __from = from_set;
                __to = to_set;
            }
            void perform()
            {
                __to->add(__point);
                __from->remove(__point);
            }
        };
    };
}

#include "Cluster.cpp"
#endif //IP_PA4_CLUSTER_H
