//
// Created by Adam on 9/17/2015.
//

#include <cmath>
#include <cstdlib>
#include <string>
#include "Point.h"
#include "Cluster.h"
#include <fstream>
#include <sstream>
#include <algorithm>

// iostream
using std::cout;
using std::endl;

// fstream
using std::ifstream;

// sstream
using std::stringstream;
using std::string;

namespace Clustering {
// Set Dimensions (for __centroid)
    void Point::setDims(int desDim)
    {
        dim = desDim;
    }

// Constructors

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
            dim = src.dim;                                  // Copy Dimension

            values = new double[dim];                       // Allocate new memory

            for (int i = 1; i < (src.getDims()+1); i++) {
                values[i-1] = src.getValue(i);                // Copy coordinates over
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
            dim = src.dim;                            // Copy Dimension

            values = new double[dim];                       // Allocate new memory

            for (int i = 0; i < src.getDims(); i++) {
                values[i] = src.getValue(i+1);                // Copy coordinates over
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
            inside += pow((p.values[i] - values[i]), 2);
        }

        double distance = sqrt(inside);
        return distance;
    }

    void Point::setValue(int dimension, double coord)     // Set a coordinate
    {
        if (dimension > (dim))
            std::cout << "That's outside this array" << std::endl;
        else
            values[dimension-1] = coord;
    }

    double Point::getValue(int dimension) const   // Get a coordinate
    {
        return values[dimension-1];
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
        if (denom == 0) {
            std::cout << "Cannot divide by zero" << std::endl;
            return *this;
        }

        for (int i = 0; i < dim; i++)
        {
            values[i] = values[i] / static_cast<double>(denom);
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
        if (denom == 0) {
            std::cout << "Cannot divide by zero" << std::endl;
            return *this;
        }

        PointPtr quotient;
        quotient = new Point(this->getDims());

        for (int i = 1; i < ((this->getDims())+1); i++)
        {

            quotient->setValue(i,this->getValue(i));
        }

        for (int i = 1; i < ((this->getDims())+1); i++)
        {

            quotient->setValue(i,(quotient->getValue(i))/denom);
        }

        return *quotient;
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
        int index;

        for (int i = 0; i < rhs.dim - 1; i++)
        {
            outputStream << rhs.values[i] << ", ";
            index = i;
        }

        outputStream << rhs.values[index + 1];
        outputStream << " : ";

        return outputStream;
    }

    std::istream &operator>>(std::istream & inputStream, Point & destPoint)
    {
        static const char DELIM = ',';

        string value;
        double d;

        int i = 1;
        while (getline(inputStream, value, DELIM)) {     // While delimiter (',') not yet reached
            d = atof(value.c_str());                    // Convert string to double
            destPoint.setValue(i++, d);                         // Post-inc 'i'
        }

    }
}
