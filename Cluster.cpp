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

        if (rhs.size == 0)
            return tempCLuster;
        else
        {
            bool add = true;
            LNodePtr rhsNode = rhs.points;
            while (rhsNode != nullptr)
            {
                add = true;
                LNodePtr lhsNode = tempCLuster.points;
                while (lhsNode != nullptr && (add == true))
                {
                    if (lhsNode->p == rhsNode->p) {
                        add = false;
                    }
                    else {
                        add = true;
                    }
                    lhsNode = lhsNode->next;
                }
                if (add == true)
                {
                    tempCLuster.add(rhsNode->p);
                }
                rhsNode = rhsNode->next;
            }
        }

        return tempCLuster;
    }


    // Intersection
    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {
        Cluster tempCluster(lhs);

        if (rhs.size == 0)
            return tempCluster;
        else
        {
            bool keep = true;
            LNodePtr tempNode;
            LNodePtr lhsNode = tempCluster.points;

            while (lhsNode != nullptr)
            {
                keep = true;
                LNodePtr rhsNode = rhs.points;

                while (rhsNode != nullptr && keep)
                {
                    if (rhsNode->p == lhsNode->p)
                    {
                        keep = false;
                    }
                    rhsNode = rhsNode->next;
                }
                if (!(keep))
                {
                    tempNode = lhsNode->next;
                    tempCluster.remove(lhsNode->p);
                    lhsNode = tempNode;
                }
                if (keep)
                    lhsNode = lhsNode->next;
            }
        }
        return tempCluster;
    }

    Cluster & Cluster::operator+=(const Cluster &rhs) {
        if (rhs.size == 0)
            return *this;
        else
        {
            bool add = true;
            LNodePtr rhsNode = rhs.points;
            while (rhsNode != nullptr)
            {
                add = true;
                LNodePtr lhsNode = this->points;
                while (lhsNode != nullptr && (add == true))
                {
                    if (lhsNode->p == rhsNode->p) {
                        add = false;
                    }
                    else {
                        add = true;
                    }
                    lhsNode = lhsNode->next;
                }
                if (add == true)
                {
                    this->add(rhsNode->p);
                }
                rhsNode = rhsNode->next;
            }
        }

        return *this;
    }

    Cluster & Cluster::operator-=(const Cluster &rhs) {
        if (rhs.size == 0)
            return *this;
        else
        {
            bool keep = true;
            LNodePtr tempNode;
            LNodePtr lhsNode = this->points;

            while (lhsNode != nullptr)
            {
                keep = true;
                LNodePtr rhsNode = rhs.points;

                while (rhsNode != nullptr && keep)
                {
                    if (rhsNode->p == lhsNode->p)
                    {
                        keep = false;
                    }
                    rhsNode = rhsNode->next;
                }
                if (!(keep))
                {
                    tempNode = lhsNode->next;
                    this->remove(lhsNode->p);
                    lhsNode = tempNode;
                }
                if (keep)
                    lhsNode = lhsNode->next;
            }
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
