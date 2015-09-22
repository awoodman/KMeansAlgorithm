//
// Created by Adam on 9/20/2015.
//

#include "Cluster.h"

namespace Clustering {

    //Copy Constructor
    Cluster::Cluster(const Cluster & src)
    {
        if (this != &src)                                       // Only do this stuff if source and this are different locations
        {
            size = src.size;                                    // Copy Size

            LNode *prevNode;                                    // Address of last node worked on
            LNode *CurrentNode;
            LNode *sourceNode;
            PointPtr newPoint;

            for (int i = 0; i < size; i++)
            {

                CurrentNode = new LNode;                        // Create new node
                CurrentNode->next = nullptr;                    // Make new node next point to null (will be overwritten)

                if (i == 0) {
                    sourceNode = src.points;                    // Source Head Pointer
                    points = CurrentNode;                       // New Head pointer points to the first node
                }
                else {
                    prevNode->next = CurrentNode;               // Make previous nodes next = the current node
                    sourceNode = sourceNode->next;              // Source node = the next source node
                }

                newPoint = new Point;                           // Create a new point dynamically

                Point newPoint(*sourceNode->p);                 // Call Point copy constructor

                CurrentNode->p = &newPoint;                     // Make CurrentNode point to location of newPoint

                prevNode = CurrentNode;                         // Copy address of current node into prevNode
            }

        }
    }

    //Assignment Operator
    Cluster &Cluster::operator=(const Cluster & src)
    {
        if (this == &src)                                   // If a = a, return a
        {
            return *this;
        }
        else                                                // Copy everything over
        {
            size = src.size;                                // Copy Size
            LNode *prevNode;                                // Address of last node worked on
            LNode *CurrentNode;
            LNode *sourceNode;
            Point *newPoint;

            for (int i = 0; i < size; i++)
            {
                if (i == 0)                                 // First Node
                {
                    sourceNode = src.points;                // Address of first source node
                    points = CurrentNode;                   // Head Pointer for new cluster
                }
                else                                        // Post First Node
                {
                    prevNode->next = CurrentNode;
                    sourceNode = sourceNode->next;
                }

                newPoint = new Point;

                Point newPoint(*sourceNode->p);

                CurrentNode->p = &newPoint;

                prevNode = CurrentNode;
            }

            return *this;                                   // this points to the calling object
        }
    }

    //Destructor
    Cluster::~Cluster()
    {
        LNode *Node;

        for (int i = 0; i < size; i++)
        {
            Node = points;
            points = Node->next;

            delete Node->p;                                 // Delete pointer to point in node

            delete Node;                                    // Delete node itself
        }
    }

    void Cluster::add(const PointPtr & newPoint)
    {
        LNode * newNode = new LNode;                        // Allocate new LNode
        newNode->next = nullptr;
        newNode->p = newPoint;
        LNode *Node;

        if (size == 0)
        {
            points = newNode;
        }
        else
        {
            Node = points;                                  // Node = address of head ptr
            for (int i = 0; i < size; i++)                  // Walk through existing node
            {
                if (newNode->p >= Node->p) {
                    newNode->next = Node->next;
                    Node->next = newNode;
                    break;
                }
                else
                {
                    Node = Node->next;
                }
            }
        }

        size++;                                             // Increment size
    }

    const PointPtr & Cluster::remove(const PointPtr & remPoint)
    {
        LNode * Node = points;                              // Node points to first node
        LNode * prevNode;

        for (int i = 0; i < size; i++)
        {
            if (Node->p == remPoint)
            {
                if (i == 0) {
                    points = Node->next;
                }
                else
                {
                    prevNode->next = Node->next;
                }
                break;
            }
            else {
                prevNode = Node;
                Node = Node->next;
            }
        }

        delete Node;

        return remPoint;
    }

    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs)
    {
        Cluster resCluster(lhs);                               // Make new cluster to copy into

        LNode * newNode = new LNode;                           // Allocate new LNode
        newNode->next = nullptr;
        newNode->p = rhs;
        LNode *Node;

        if (lhs.size == 0)
        {
            resCluster.points = newNode;
            newNode->p = rhs;
        }
        else
        {
            Node = lhs.points;                                  // Node = address of headptr
            for (int i = 0; i < lhs.size; i++)                  // Walk through existing node
            {
                if (newNode->p >= Node->p) {
                    newNode->next = Node->next;
                    Node->next = newNode;
                    break;
                }
                else
                {
                    Node = Node->next;
                }
            }
        }

        resCluster.size++;                                             // Increment size

        return resCluster;
    }

    const Cluster operator-(const Cluster &sourceCluster, const PointPtr &sourcePoint)
    {
        Cluster resCluster(sourceCluster);                            // Copy lhs into 'result' cluster

        LNode * Node = sourceCluster.points;                 // Node points to first node in source cluster
        LNode * prevNode;                                   // Pointer to previous node

        for (int i = 0; i < sourceCluster.size; i++)
        {
            if (Node->p == sourcePoint)                             // if node point = what we're subtracting
            {
                if (i == 0) {
                    resCluster.points = Node->next;                 // set headptr to next, removing first node from res
                }
                else
                {
                    prevNode->next = Node->next;                    // Remove link from middle of list
                }
                break;
            }
            else {
                prevNode = Node;                                    // set previous to current
                Node = Node->next;                                  // go to next link
            }
        }

        delete Node;
        resCluster.size--;
        return resCluster;
    }

    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {
        LNode *rhsNode = rhs.points;                        // rhsNode is pointer to rhs cluster "points"
        LNode *lhsNode = lhs.points;                        // lhsNode is pointer to rhs cluster "points"

        if (lhs.size != rhs.size) {
            return false;
        }
        for (int i = 0; i < lhs.size; i++)
        {
            if (rhsNode->p != lhsNode->p) {
                return false;
            }

            rhsNode = rhsNode->next;
            lhsNode = lhsNode->next;
        }

        return true;
    }

    //Union
    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {

        bool add;
        Cluster result(lhs);
        LNode *lhsNode;
        LNode *rhsNode = rhs.points;

        while (rhsNode != nullptr) {

            lhsNode = lhs.points;
            add = true;

            while (lhsNode != nullptr) {
                if (lhsNode->p == rhsNode->p) {
                    add = false;
                    break;
                }
                lhsNode = lhsNode->next;
            }
            if (add == true) {
                result.add(rhsNode->p);
                rhsNode = rhsNode->next;
            }

            return result;
        }
    }

    // Intersection
    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {

        bool remove;
        Cluster result(lhs);
        LNode *lhsNode;
        LNode *rhsNode = rhs.points;

        while (rhsNode != nullptr) {                       // loop through all points in the right cluster
            remove = false;
            lhsNode = lhs.points;
            while (lhsNode != nullptr) {                  // loop through all points in the left cluster
                if (lhsNode->p == rhsNode->p) {    // if the point is in both clusters dont remove it
                    remove = true;
                    break;
                }
                lhsNode = lhsNode->next;
            }
            if (remove == true)                               // if the point wasnt in both clusters remove it.
                result.remove(rhsNode->p);
            rhsNode = rhsNode->next;
        }
        return result;
    }

    Cluster & Cluster::operator+=(const Cluster &rhs) {
        bool add;
        LNode *thisNode;
        LNode *rhsNode = rhs.points;

        while (rhsNode != nullptr) {
            thisNode = this->points;
            add = true;
            while (thisNode != nullptr) {
                if (thisNode->p == rhsNode->p) {
                    add=false;
                    break;
                }
                thisNode = thisNode->next;
            }
            if (add == true) {
                this->add(rhsNode->p);
                rhsNode = rhsNode->next;
            }

            return *this;
        }
    }

    Cluster & Cluster::operator-=(const Cluster &rhs) {
        bool remove;
        LNode *thisNode = this->points;
        LNode *rhsNode;

        while (thisNode != nullptr) {                       // loop through all points in the left cluster
            remove = false;
            rhsNode = rhs.points;
            while (rhsNode != nullptr) {                  // loop through all points in the right cluster
                if (thisNode->p == rhsNode->p) {    // if the point is in both clusters remove it
                    remove = true;
                    break;
                }
                rhsNode = rhsNode->next;
            }
            if (remove == true)                               // if the point was in both clusters so remove it.
                this->remove(thisNode->p);
            thisNode = thisNode->next;
        }
        return *this;
    }

    Cluster & Cluster::operator+=(const Point & rhs)
    {
        this->add((const PointPtr)&rhs);

        return *this;
    }

    Cluster & Cluster::operator-=(const Point &rhs)
    {
        this->remove((const PointPtr)&rhs);

        return *this;
    }

//    std::ostream & operator<<(std::ostream & os, const Cluster & sourceCluster)
//    {
//        LNode *thisNode = sourceCluster.points;
//
//        while(thisNode != nullptr) {
//            os << *thisNode->p;
//            thisNode = thisNode->next;
//        }
//
//        return os;
//    }
}
