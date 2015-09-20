//
// Created by Adam on 9/17/2015.
//

#include <cmath>
#include "Point.h"

namespace Clustering {

// Constructors
    Point::Point()
    {
        std::cout << "There is no default constructor in place.  Sorry!" << std::endl;
    }

    Point::Point(int dimension)     // Constructor to set all coordinates to 0
    {
        dim = dimension;

        values = new double[dim];

        for (int i = 0; i < dim; i++) {
            values[i] = 0;
        }
    }

    Point::Point(int dimension, double *array)      // Constructor to pass in an array
    {
        dim = dimension;

        values = new double[dim];

        for (int i = 0; i < dim; i++) {
            values[i] = array[i];
        }
    }

    //Copy Constructor
    Point::Point(const Point & src)                         // Pass in source point
    {
        if (this != &src)                                    // Only do this stuff if source and this are different locations
        {
            dim = src.getDims();                           // Copy Dimension

            values = new double[dim];                       // Allocate new memory

            for (int i = 0; i < src.getDims(); i++) {
                values[i] = src.getValue(i);                // Copy coordinates over
            }
        }
        else {
            values = NULL;                                  // I don't want this to point anywhere
        }
    }

    //Assignment Operator
    Point& Point::operator=(const Point & src)
    {
        if (this == &src)                                   // If a = a, return a
        {
            return *this;
        }
        else
        {
            dim = src.getDims();                            // Copy Dimension

            values = new double[dim];                       // Allocate new memory

            for (int i = 0; i < src.getDims(); i++) {
                values[i] = src.getValue(i);                // Copy coordinates over
            }

            return *this;                                   // this points to the calling object
        }
    }

    //Destructor
    // Dynamic allocation for coordinates array, so must deallocate (delete) the memory
    Point::~Point() {
        delete[] values;
    }

    double Point::distanceTo(const Point &p) const         // Distance to, with any number of dims
    {
        double inside = 0;

        for (int i = 0; i < dim; i++) {
            inside += pow((p.getValue(i) - values[i]), 2);
        }

        double distance = sqrt(inside);
        return distance;
    }

    void Point::setValue(int dimension, double coord)     // Set a coordinate
    {
        values[dimension] = coord;
    }

    double Point::getValue(int dimension) const   // Get a coordinate
    {
        return values[dimension];
    }


    // Members
    Point& Point::operator*=(double multiplier)
    {
        for (int i = 0; i < dim; i++)
        {
            values[i] = values[i]*multiplier;
        }

        return *this;
    }

    Point& Point::operator/=(double denom)
    {
        for (int i = 0; i < dim; i++)
        {
            values[i] = values[i]/denom;
        }

        return *this;
    }

    const Point Point::operator*(double multiplier) const
    {
        Point product(this->getDims());

        for (int i = 0; i < this->getDims(); i++)
        {
            product.setValue(i,this->getValue(i));
        }

        for (int i = 0; i < this->getDims(); i++)
        {

            product.setValue(i,(product.getValue(i))*multiplier);
        }

        return product;
    }

    const Point Point::operator/(double denom) const
    {
        Point product(this->getDims());

        for (int i = 0; i < this->getDims(); i++)
        {
            product.setValue(i,this->getValue(i));
        }

        for (int i = 0; i < this->getDims(); i++)
        {

            product.setValue(i,(product.getValue(i))/denom);
        }

        return product;
    }

    Point &operator+=(Point & dst, const Point & src)
    {
        for (int i = 0; i < dst.getDims(); i++)
        {
            dst.values[i] = dst.values[i] + src.values[i];
        }

        return dst;
    }

    Point &operator-=(Point & dst, const Point & src)
    {
        for (int i = 0; i < dst.getDims(); i++)
        {
            dst.values[i] = dst.values[i] - src.values[i];
        }

        return dst;
    }

    const Point operator+(const Point & lhs, const Point & rhs)
    {
        Point result(lhs.getDims());

        for (int i = 0; i < lhs.getDims(); i++)
        {
            result.setValue(i,(lhs.values[i]+rhs.values[i]));
        }

        return result;
    }

    const Point operator-(const Point & lhs, const Point & rhs)
    {
        Point result(lhs.getDims());

        for (int i = 0; i < lhs.dim; i++)
        {
            result.setValue(i,(lhs.values[i]-rhs.values[i]));
        }

        return result;
    }

    bool operator==(const Point & lhs, const Point & rhs)
    {
        for (int i  = 0; i < lhs.dim; i++)
        {
            if (lhs.values[i] != rhs.values[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Point & lhs, const Point & rhs)
    {
        bool decision;
        for (int i  = 0; i < lhs.dim; i++)
        {
            if (lhs.values[i] == rhs.values[i])
            {
                decision = false;
            }
            else
                return true;
        }

        return decision;
    }

    bool operator<(const Point & lhs, const Point & rhs)
    {
        bool decision;
        for (int i  = 0; i < lhs.dim; i++)
        {
            if (lhs.values[i] > rhs.values[i])
            {
                return false;
            }
            else if (lhs.values[i] == rhs.values[i])
                decision = false;
            else if (lhs.values[i] < rhs.values[i])
                return true;
        }
        return decision;
    }

    bool operator>(const Point & lhs, const Point & rhs)
    {
        bool decision;
        for (int i  = 0; i < lhs.dim; i++)
        {
            if (lhs.values[i] < rhs.values[i])
            {
                return false;
            }
            else if (lhs.values[i] == rhs.values[i])
                decision = false;
            else if (lhs.values[i] > rhs.values[i])
                return true;
        }
        return decision;
    }

    bool operator<=(const Point & lhs, const Point & rhs)
    {
        bool decision = true;
        for (int i  = 0; i < lhs.dim; i++)
        {
            if (lhs.values[i] > rhs.values[i])
            {
                return false;
            }
            else if (lhs.values[i] == rhs.values[i])
            {
                decision = true;
            }
            else if (lhs.values[i] < rhs.values[i])
                return true;
        }
        return decision;
    }

    bool operator>=(const Point & lhs, const Point & rhs)
    {
        bool decision = true;
        for (int i  = 0; i < lhs.dim; i++)
        {
            if (lhs.values[i] < rhs.values[i])
            {
                return false;
            }
            else if (lhs.values[i] == rhs.values[i])
            {
                decision = true;
            }
            else if (lhs.values[i] > rhs.values[i])
                return true;
        }
        return decision;
    }

    std::ostream &operator<<(std::ostream & outputStream, const Point & rhs)
    {
        for (int i = 0; i < rhs.dim; i++)
        {
            outputStream << rhs.values[i] << " ";
        }

        return outputStream;
    }
}