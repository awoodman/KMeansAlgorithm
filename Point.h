//
// Created by Adam on 11/4/2015.
//

#ifndef IP_PA4_POINT_H
#define IP_PA4_POINT_H

#include <iostream>
#include <vector>
#include "Exceptions.h"

using std::vector;
using std::cout;
using std::endl;
using std::endl;

namespace Clustering {
    template <typename T, int dim>
    class Point {
    private:
        unsigned int __dim;
        vector<T> values;
        unsigned int __id;
    public:
        // Constructors
        Point();
        Point(unsigned int);
        Point(unsigned int, T*);

        // Big 3 (cpy const, assign op, destr)
        Point(const Point<T,dim> &);
        Point &operator=(const Point<T,dim> &);
        ~Point();

        // ID Gen
        void generateID();
        unsigned int getID() const { return __id; }

        // Distance Function
        double distanceTo(const Point<T,dim> &) const;

        // Accessors & Mutators for data
        void setDims(unsigned int);
        unsigned int getDims() const { return __dim; }
        void setValue(unsigned int, T);
        T getValue(unsigned int index) const { return values[index]; }

        // Member Functions
        Point &operator*=(double);
        Point &operator/=(double);
        const Point operator*(double) const;
        const Point operator/(double) const;
        T& operator[](unsigned int index)
        {
            if (index >= 0 && index < __dim)
                return values[index];
            else {
                cout << "Out of bounds" << endl;
                //TODO: Return what here?
            }
        }

        // Friend Functions
        template <typename S, int _dim>
        friend Point<S,_dim> &operator+=(Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend Point<S,_dim> &operator-=(Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend const Point<S,_dim> operator+(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend const Point<S,_dim> operator-(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend bool operator==(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend bool operator!=(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend bool operator<(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend bool operator>(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend bool operator<=(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend bool operator>=(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend std::ostream &operator<<(std::ostream &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend std::istream &operator>>(std::istream &, Point<S,_dim> &);
    };
}

#include "Point.cpp"
#endif //IP_PA4_POINT_H
