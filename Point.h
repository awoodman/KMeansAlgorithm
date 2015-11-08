//
// Created by Adam on 11/4/2015.
//

#ifndef IP_PA4_POINT_H
#define IP_PA4_POINT_H

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

typedef double dataType;

namespace Clustering {
    class Point {
    private:
        unsigned int __dim;
        vector<dataType> values;
        unsigned int __id;
    public:
        // Constructors
        Point(unsigned int);
        Point(unsigned int, double*);

        // Big 3 (cpy const, assign op, destr)
        Point(const Point &);
        Point &operator=(const Point &);
        ~Point();

        // ID Gen
        void generateID();

        // Distance Function
        double distanceTo(const Point &) const;

        // Accessors & Mutators for data
        void setDims(unsigned int);
        unsigned int getDims() const { return __dim; }
        void setValue(unsigned int, dataType);
        dataType getValue(unsigned int index) const { return values[index]; }

        // Member Functions
        Point &operator*=(double);
        Point &operator/=(double);
        const Point operator*(double) const;
        const Point operator/(double) const;
        dataType& operator[](unsigned int index)
        {
            if (index >= 0 && index < __dim)
                return values[index];
            else {
                cout << "Out of bounds" << endl;
                //TODO: Return what here?
            }
        }

        // Friend Functions
        friend Point &operator+=(Point &, const Point &);
        friend Point &operator-=(Point &, const Point &);
        friend const Point operator+(const Point &, const Point &);
        friend const Point operator-(const Point &, const Point &);
        friend bool operator==(const Point &, const Point &);
        friend bool operator!=(const Point &, const Point &);
        friend bool operator<(const Point &, const Point &);
        friend bool operator>(const Point &, const Point &);
        friend bool operator<=(const Point &, const Point &);
        friend bool operator>=(const Point &, const Point &);
        friend std::ostream &operator<<(std::ostream &, const Point &);
        friend std::istream &operator>>(std::istream &, Point &);
    };
}

#include "Point.cpp"
#endif //IP_PA4_POINT_H
