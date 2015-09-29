//
// Created by Adam on 9/20/2015.
//

#include "Cluster.h"

namespace Clustering {

    //Copy Constructor
    Cluster::Cluster(const Cluster & src)
    {
        if (src.points == nullptr)
        {
            this->size = 0;
            this->points = nullptr;
        }
        else
        {
            this->size = src.size;
            LNodePtr currNode;
            LNodePtr prevNode;
            LNodePtr copyNode = src.points;
            int i = 1;
            while(copyNode != nullptr) {
                currNode = new LNode;
                if (i > 1) {
                    prevNode->next = currNode;
                }
                currNode->next = nullptr;
                if (i == 1) {
                    this->points = currNode;
                }
                currNode->p = copyNode->p;
                copyNode = copyNode->next;
                prevNode = currNode;
                i++;
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
            // Delete the existing list
            LNodePtr node = this->points;         // "Current Node" to traverse old list and delete it
            LNodePtr nextNode;

            while (node != nullptr)                 // Clear existing linked list
            {
                nextNode = node->next;
                delete node;
                node = nextNode;
                this->size--;
            }

            if (src.size == 0)
                this->points = nullptr;
            else
            {
                int i = 1;
                LNodePtr sourceNode = src.points;
                LNodePtr prevNode;
                while (sourceNode != nullptr)
                {
                    LNodePtr newNode = new LNode;
                    if (i == 1)
                    {
                        this->points = newNode;
                    }
                    newNode->next = nullptr;
                    if (i > 1)
                    {
                        prevNode->next = newNode;
                    }
                    newNode->p = sourceNode->p;
                    sourceNode = sourceNode->next;
                    prevNode = newNode;
                    i++;
                    this->size++;
                }
            }
        }
        return *this;
    }

    //Destructor
    Cluster::~Cluster()
    {
        LNodePtr node = this->points;         // "Current Node" to traverse old list and delete it
        LNodePtr nextNode;

        while (node != nullptr)
        {
            nextNode = node->next;
            delete node;
            node = nextNode;
        }
    }

    void Cluster::add(const PointPtr & newPoint)
    {
        LNode *node = this->points;
        LNodePtr prevnode;
        LNodePtr newnode = new LNode;
        newnode->next = nullptr;
        newnode->p = newPoint;

        if(size == 0)                                                   // empty cluster, just point to newnode
            this->points = newnode;
        else {
            while (node != nullptr) {                               // dont walk of the end of the node list
                if (*newnode->p <= *node->p) {                   // newnode goes before node
                    if (node == this->points) {              //  newnode will be first node now
                        newnode->next = this->points;
                        this->points = newnode;
                    } else {                                //  newnode goes between prevnode and node
                        newnode->next = prevnode->next;
                        prevnode->next = newnode;
                    }
                    this->size++;                            // all done, inc size and return
                    return;
                }
                prevnode = node;
                node = node->next;
            }
            prevnode->next = newnode;                               // newnode is now last node
        }
        this->size++;
    }

    const PointPtr & Cluster::remove(const PointPtr & remPoint)
    {
        LNodePtr node = this->points;
        LNodePtr prevNode;
        bool remove = false;
        if (node != nullptr)                            // If at least one node is in the list
        {
            if (remPoint == node->p)                    // If first node is what we're removing
            {
                this->points = node->next;              // Remove first node from list
                delete node;                            // Delete first node
                remove = true;
                this->size--;
            }
            else
            {
                while (node != nullptr && !(remove)) {                   // While not at end of list
                    prevNode = node;                        // Node before "node"
                    node = node->next;                      // Go to next node for comparison
                    if (remPoint == node->p) {
                        prevNode->next = node->next;        // Remove the node
                        delete node;
                        remove = true;
                        this->size--;
                    }
                }
            }
        }
        return remPoint;
    }

    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs)
    {
        Cluster tempCluster(lhs);                           //Create temporary cluster to return, copying from lhs
        tempCluster.add(rhs);                               // Implement add()
        return tempCluster;
    }

    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs)
    {
        Cluster tempCluster(lhs);                           // Copy c into temp
        tempCluster.remove(rhs);                            // Implement remove()
        return tempCluster;
    }

    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {
        LNodePtr rhsNode = rhs.points;                        // rhsNode is pointer to rhs cluster "points"
        LNodePtr lhsNode = lhs.points;                        // lhsNode is pointer to lhs cluster "points"
        bool decision = true;

        //3 Potential Cases
        if (lhs.size != rhs.size) {                        // If cluster sizes aren't the same
            return false;
        }
        else if ((lhs.size == 0) && (rhs.size == 0))                            // If both clusters have 0
        {
            return true;
        }
        else {                                              // If sizes are greater than 0
            while ((rhsNode != nullptr) && (lhsNode != nullptr) && (decision == true))
            {
                if (lhsNode->p == rhsNode->p)
                {
                    decision = true;
                    lhsNode = lhsNode->next;
                    rhsNode = rhsNode->next;
                }
                else
                    return false;
            }
            return decision;
        }
    }


    //Union
    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {
        Cluster tempCLuster(lhs);
        bool add;

        if (tempCLuster.size == 0)
        {
            if (rhs.size == 1)
            {
                LNodePtr node = rhs.points;
                tempCLuster.add(node->p);
            }
            else {
                LNodePtr copyNode = rhs.points;
                LNodePtr nextCopyNode = copyNode->next;

                do {
                    tempCLuster.add(copyNode->p);
                    copyNode = copyNode->next;
                    nextCopyNode = nextCopyNode->next;
                } while (nextCopyNode != nullptr);
            }
        }

        else if (tempCLuster.size == 1)
        {
            if (rhs.size > 1) {
                LNodePtr tempNode = tempCLuster.points;
                LNodePtr copyNode = rhs.points;
                LNodePtr nextCopyNode = copyNode->next;

                do {
                    if (tempNode->p == copyNode->p)
                        add = false;
                    else
                        add = true;

                    if (add)
                        tempCLuster.add(copyNode->p);

                    copyNode = copyNode->next;
                    nextCopyNode = nextCopyNode->next;

                } while (nextCopyNode != nullptr);
            }
            else
            {
                LNodePtr tempNode = tempCLuster.points;
                LNodePtr copyNode = rhs.points;

                if (tempNode->p != copyNode->p)
                    tempCLuster.add(copyNode->p);
            }
        }

        else {
            LNodePtr tempNode = tempCLuster.points;
            LNodePtr nextTempNode = tempNode->next;
            LNodePtr copyNode = rhs.points;
            LNodePtr nextCopyNode = copyNode->next;

            do {
                do {
                    if (tempNode->p != copyNode->p) {
                        tempNode = tempNode->next;
                        nextTempNode = nextTempNode->next;
                        add = true;
                    }
                    else
                        add = false;
                } while (nextTempNode != nullptr && add);

                if (add) {
                    tempCLuster.add(copyNode->p);
                }
                copyNode = copyNode->next;
                nextCopyNode = nextCopyNode->next;
            } while (nextCopyNode != nullptr);
        }
        return tempCLuster;
    }

    //////////////////////////////  LEFT OFF HERE  ///////////////////////////////////

    // Intersection
    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {

        bool remove;
        Cluster result(lhs);
        LNodePtr lhsNode;
        LNodePtr rhsNode = rhs.points;

        while (rhsNode != nullptr) {                       // loop through all points in the right cluster
            remove = false;
            lhsNode = lhs.points;
            while (lhsNode != nullptr) {                     // loop through all points in the left cluster
                if (lhsNode->p == rhsNode->p) {             // if the point is in both clusters dont remove it
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

    Cluster & Cluster::operator+=(const Point & rhs)        // Creates a new point on the heap
    {
        PointPtr newPoint = new Point(rhs);
        this->add(newPoint);
        return *this;
    }

    Cluster & Cluster::operator-=(const Point &rhs)         // Removes ONE instance on the point passed
    {
        bool found = false;
        if (this->points == nullptr)
            return *this;
        else {
            LNodePtr node = this->points;
            LNodePtr prevNode;
            int i = 1;
            while (!(found) && node != nullptr) {
                if (*(node->p) == rhs)
                {
                    if (i == 1)
                        this->points = node->next;
                    if (i > 1)
                        prevNode->next = node->next;
                    delete node;
                    found = true;
                    this->size--;
                }
                i++;
                prevNode = node;
                node = node->next;
            }
        }
        if (!(found))
            std::cout << "Could not find this point in the cluster" << std::endl;

        return *this;
    }

}
