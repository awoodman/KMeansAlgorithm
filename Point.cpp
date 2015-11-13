//
// Created by Adam on 11/4/2015.
//
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#include "Point.h"

using std::string;

namespace Clustering {
    template <typename T,int dim>
    Point<T,dim>::Point() : __dim(dim) {
        generateID();
        for (int i = 0; i < __dim; i++) {
            values.push_back(0);
        }
    };

    template <typename T,int dim>
    Point<T,dim>::Point(unsigned int dims) {
        __dim = dims;
        generateID();
        for (int i = 0; i < __dim; i++) {
            values.push_back(0);    // Initially set all coords as 0
        }
    }

    template <typename T,int dim>
    Point<T,dim>::Point(unsigned int dims, T *array) {
        __dim = dims;
        generateID();
        for (int i = 0; i < __dim; i++) {
            values.push_back(array[i]);    // Set all coords as array data
        }
    }

    template <typename T,int dim>
    Point<T,dim>::Point(const Point<T,dim> &src) {
        __id = src.__id;
        __dim = src.__dim;
        values = src.values;
    }

    template <typename T,int dim>
    Point<T,dim>& Point<T,dim>::operator=(const Point<T,dim> & src) {
        if (this->__id != src.__id)
        {
            __id = src.__id;
            __dim = src.__dim;
            values = src.values;
        }

        return *this;
    }

    template <typename T,int dim>
    Point<T,dim>::~Point() {
        //TODO: Destruct What??
    }

    template <typename T,int dim>
    void Point<T,dim>::generateID()
    {
        static unsigned int id = 1;
        __id = id++;
    }

    template <typename T,int dim>
    double Point<T,dim>::distanceTo(const Point<T,dim> &p) const {
        double inside = 0;

        for (int i = 0; i < __dim; i++) {
            inside += pow((this->values[i] - p.values[i]),2);
        }

        double distance = sqrt(inside);
        return distance;
    }

    template <typename T,int dim>
    void Point<T,dim>::setDims(unsigned int dims) {
        __dim = dims;
    }

    template <typename T,int dim>
    void Point<T,dim>::setValue(unsigned int index, T data)
    {
        values[index] = data;
    }

    template <typename T,int dim>
    Point<T,dim> & Point<T,dim>::operator*=(double multiplier) {
        for (int i = 0; i < __dim; i++)
            values[i] = values[i] * multiplier;

        return *this;
    }

    template <typename T,int dim>
    Point<T,dim> & Point<T,dim>::operator/=(double denominator)
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

    template <typename T,int dim>
    const Point<T,dim> Point<T,dim>::operator*(double multiplier) const {
        Point<T,dim> product(*this);
        product*=multiplier;
        return product;
    }

    template <typename T,int dim>
    const Point<T,dim> Point<T,dim>::operator/(double denominator) const {
        Point<T,dim> quotient(*this);
        quotient/=denominator;
        return quotient;
    }

    template <typename S, int dim>
    Point<S,dim> &operator+=(Point<S,dim> & dst, const Point<S,dim> & src) {
        if (dst.__dim == src.__dim) {
            for (int i = 0; i < src.__dim; i++) {
                dst.values[i] = dst.values[i] + src.values[i];
            }
        }
        else
            cout << "The dimensions of these points are different" << endl;
    }

    template <typename S, int dim>
    Point<S,dim> &operator-=(Point<S,dim> & dst, const Point<S,dim> & src) {
        if (dst.__dim == src.__dim) {
            for (int i = 0; i < src.__dim; i++) {
                dst.values[i] = dst.values[i] - src.values[i];
            }
        }
        else
            cout << "The dimensions of these points are different" << endl;
    }

    template <typename S, int dim>
    const Point<S,dim> operator+(const Point<S,dim> & dst, const Point<S,dim> & src) {
        if (dst.__dim == src.__dim) {
            Point<S,dim> sum(dst);
            for (int i = 0; i < src.__dim; i++) {
                sum.values[i] = sum.values[i] + src.values[i];
            }
        }
        else
            cout << "The dimensions of these points are different" << endl;
    }

    template <typename S, int dim>
    const Point<S,dim> operator-(const Point<S,dim> & dst, const Point<S,dim> & src) {
        if (dst.__dim == src.__dim) {
            Point<S,dim> sum(dst);
            for (int i = 0; i < src.__dim; i++) {
                sum.values[i] = sum.values[i] - src.values[i];
            }
        }
        else
            cout << "The dimensions of these points are different" << endl;
    }

    template <typename S, int dim>
    bool operator==(const Point<S,dim> & lhs, const Point<S,dim> & rhs) {
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

    template <typename S, int dim>
    bool operator!=(const Point<S,dim> & lhs, const Point<S,dim> & rhs) {
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

    template <typename S, int dim>
    bool operator<(const Point<S,dim> & lhs, const Point<S,dim> & rhs) {
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

    template <typename S, int dim>
    bool operator>(const Point<S,dim> & lhs, const Point<S,dim> & rhs) {
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

    template <typename S, int dim>
    bool operator<=(const Point<S,dim> & lhs, const Point<S,dim> & rhs) {
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

    template <typename S, int dim>
    bool operator>=(const Point<S,dim> & lhs, const Point<S,dim> & rhs) {
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

    template <typename S, int dim>
    std::ostream &operator<<(std::ostream & outputStream, const Point<S,dim> & pt) {
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

    template <typename S, int dim>
    std::istream &operator>>(std::istream & inputStream, Point<S,dim> & pt) {
        static const char DELIM = ',';
        string value;
        S d;

        int i = 0;
        while (getline(inputStream, value, DELIM)) {     // While delimiter (',') not yet reached
            d = atof(value.c_str());                    // Convert string to double
            pt.setValue(i++,d);                         // Post-inc 'i'
        }
        return inputStream;
    }
}