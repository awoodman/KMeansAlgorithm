//
// Created by Adam on 9/20/2015.
//

#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include "Point.h"

namespace Clustering {

    typedef Point *PointPtr;                    // Pointer to a point (goes inside node)
    typedef struct LNode *LNodePtr;             // Pointer to an LNode

    struct LNode {                              // linked-list node
        PointPtr p;
        LNodePtr next;
                            // could add this: LNode(PointPtr pt, LNodePtr n) : p(pt), next(n) {}  // Node Constructor
    };

    class Cluster {
        int size;
        int __dimensionality;
        LNodePtr points;                        // linked-list head (points to first node)
        bool __release_points = false;
        unsigned int __id;
        PointPtr __centroid;
        bool __valid_centroid;

    public:
        // Set the ID
        void generateID();

        Cluster() : size(0), points(nullptr), __dimensionality(0), __valid_centroid(false), __centroid(nullptr) { generateID(); };

        // The big three: cpy constructor, overloaded operator=, destructor
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();

        // Point Getter
        PointPtr getPoint(int);

        // ID Getter
        int getID() const { return __id; }

        // Dimensionality Setter
        void setDimensionality(const int);

        // Centroid Operations
        void setCentroid(const Point &);
        void invalidateCentroid();
        const Point getCentroid();
        void computeCentroid();

        bool validCentroid()
        {
            if (__valid_centroid)
                return true;
            else
                return false;
        }

        //9 - 11 Instructions Functions
        void pickPoints(int k, PointPtr *pointArray);
        int getSize();
        double intraClusterDistance() const;
        friend double interClusterDistance(const Cluster &, const Cluster &);
        int getClusterEdges();

        // Release Point t/f
        void rpTrue() {__release_points = true; }
        void rpFalse() {__release_points = false; }

        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const PointPtr &);
        const PointPtr &remove(const PointPtr &);

        // Overloaded operators

        // Set-preserving operators (do not duplicate points in the space)
        // Friends
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);

        // Members
        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference

        Cluster &operator+=(const Point &rhs); // add point
        Cluster &operator-=(const Point &rhs); // remove point

        // Set-destructive operators (duplicate points in the space)
        // Friends
        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);

//         IO
        friend std::ostream &operator<<(std::ostream &, Cluster &);
        friend std::istream &operator>>(std::istream &, Cluster &);

        class Move {
        private:
            Cluster* from;
            Cluster* to;
            PointPtr point;
        public:
            Move(const PointPtr ptr, Cluster * from_set, Cluster * to_set)
            {
                point = ptr;
                this->from = from_set;
                this->to = to_set;
            }
            void perform()
            {
                to->add(from->remove(point));
            }
        };
    };
}
#endif //CLUSTERING_CLUSTER_H