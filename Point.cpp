//
// Created by Adam on 11/4/2015.
//

#include "Point.h"
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using std::string;

namespace Clustering {
    Point::Point(unsigned int dim) {
        __dim = dim;
        generateID();
        for (int i = 0; i < __dim; i++) {
            values.push_back(0);    // Initially set all coords as 0
        }
    }

    Point::Point(unsigned int dim, dataType *array) {
        __dim = dim;
        generateID();
        for (int i = 0; i < __dim; i++) {
            values.push_back(array[i]);    // Set all coords as array data
        }
    }

    Point::Point(const Point &src) {
        __id = src.__id;
        __dim = src.__dim;
        values = src.values;
    }

    Point& Point::operator=(const Point & src) {
        if (this->__id != src.__id)
        {
            __id = src.__id;
            __dim = src.__dim;
            values = src.values;
        }

        return *this;
    }

    Point::~Point() {
        //TODO: Destruct What??
    }

    void Point::generateID()
    {
        static unsigned int id = 1;
        __id = id++;
    }

    double Point::distanceTo(const Point &p) const {
        double inside = 0;

        for (int i = 0; i < __dim; i++) {
            inside += pow((this->values[i] - p.values[i]),2);
        }

        double distance = sqrt(inside);
        return distance;
    }

    void Point::setDims(unsigned int dim) {
        __dim = dim;
    }

    void Point::setValue(unsigned int index, dataType data)
    {
        values[index] = data;
    }

    Point & Point::operator*=(double multiplier) {
        for (int i = 0; i < __dim; i++)
            values[i] = values[i] * multiplier;

        return *this;
    }

    Point & Point::operator/=(double denominator)
    {
        if (denominator != 0) {
            for (int i = 0; i < __dim; i++) {
                values[i] = values[i] / denominator;
            }
        }
        else
            cout << "Cannot divide by zero" << endl;

        return *this;
    }

    const Point Point::operator*(double multiplier) const {
        Point product(*this);
        product*=multiplier;
        return product;
    }

    const Point Point::operator/(double denominator) const {
        Point quotient(*this);
        quotient/=denominator;
        return quotient;
    }

    Point &operator+=(Point & dst, const Point & src) {
        if (dst.__dim == src.__dim) {
            for (int i = 0; i < src.__dim; i++) {
                dst.values[i] = dst.values[i] + src.values[i];
            }
        }
        else
            cout << "The dimensions of these points are different" << endl;
    }

    Point &operator-=(Point & dst, const Point & src) {
        if (dst.__dim == src.__dim) {
            for (int i = 0; i < src.__dim; i++) {
                dst.values[i] = dst.values[i] - src.values[i];
            }
        }
        else
            cout << "The dimensions of these points are different" << endl;
    }

    const Point operator+(const Point & dst, const Point & src) {
        if (dst.__dim == src.__dim) {
            Point sum(dst);
            for (int i = 0; i < src.__dim; i++) {
                sum.values[i] = sum.values[i] + src.values[i];
            }
        }
        else
            cout << "The dimensions of these points are different" << endl;
    }

    const Point operator-(const Point & dst, const Point & src) {
        if (dst.__dim == src.__dim) {
            Point sum(dst);
            for (int i = 0; i < src.__dim; i++) {
                sum.values[i] = sum.values[i] - src.values[i];
            }
        }
        else
            cout << "The dimensions of these points are different" << endl;
    }

    bool operator==(const Point & lhs, const Point & rhs) {
        if (lhs.__id != rhs.__id)
            return false;
        else if (lhs.__dim != rhs.__dim)
            return false;
        else {
            for (int i = 0; i < lhs.__dim; i++) {
                if (lhs.values[i] != rhs.values[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    bool operator!=(const Point & lhs, const Point & rhs) {
        bool decision;
        if (lhs.__id == rhs.__id)
            return false;
        else if (lhs.__dim != rhs.__dim)
            return true;
        else {
            for (int i = 0; i < lhs.__dim; i++) {
                if (lhs.values[i] == rhs.values[i])
                    decision = false;
                else
                    return true;
            }
        }
        return decision;
    }

    bool operator<(const Point & lhs, const Point & rhs) {
        if (lhs.__dim == rhs.__dim) {
            bool decision;
            for (int i = 0; i < lhs.__dim; i++) {
                if (lhs.values[i] > rhs.values[i])
                {
                    return false;
                }
                else if (lhs.values[i] == rhs.values[i])
                    decision = false;
                else if (lhs.values[i] < rhs.values[i])
                    return true;
            }
        }
        else
            cout << "The dimensions of these points are different" << endl;
    }

    bool operator>(const Point & lhs, const Point & rhs) {
        if (lhs.__dim == rhs.__dim) {
            bool decision;
            for (int i = 0; i < lhs.__dim; i++) {
                if (lhs.values[i] < rhs.values[i])
                {
                    return false;
                }
                else if (lhs.values[i] == rhs.values[i])
                    decision = false;
                else if (lhs.values[i] > rhs.values[i])
                    return true;
            }
        }
        else
            cout << "The dimensions of these points are different" << endl;
    }

    bool operator<=(const Point & lhs, const Point & rhs) {
        bool decision = true;
        for (int i = 0; i < lhs.__dim; i++)
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

    bool operator>=(const Point & lhs, const Point & rhs) {
        bool decision = true;
        for (int i  = 0; i < lhs.__dim; i++)
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

    std::ostream &operator<<(std::ostream & outputStream, const Point & pt) {
        int index;

        for (int i = 0; i < (pt.__dim - 1); i++)
        {
            outputStream << pt.getValue(i) << ", ";
            index = i + 1;
        }

        outputStream << pt.getValue(index);
        outputStream << " : ";

        return outputStream;
    }

    std::istream &operator>>(std::istream & inputStream, Point & pt) {
        static const char DELIM = ',';
        string value;
        dataType d;

        int i = 0;
        while (getline(inputStream, value, DELIM)) {     // While delimiter (',') not yet reached
            d = atof(value.c_str());                    // Convert string to double
            pt.setValue(i++,d);                         // Post-inc 'i'
        }
    }
}