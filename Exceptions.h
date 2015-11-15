//
// Created by Adam on 11/14/2015.
//

#ifndef IP_PA4_EXCEPTIONS_H
#define IP_PA4_EXCEPTIONS_H

#include <iostream>
#include <string>

namespace Clustering {
    class DimensionalityMismatchEx {
    private:
        unsigned int __correctDim, __incorrectDim;
        std::string __name;
    public:
        DimensionalityMismatchEx(unsigned int, unsigned int);
        std::string getName() { return __name; };
        unsigned int getIncorrectData() { return __incorrectDim; };
        friend std::ostream &operator<<(std::ostream &, const DimensionalityMismatchEx &);
    };

    class OutOfBoundsEx {
    private:
        int __incorrectIndex;
        int __minIndex;
        int __maxIndex;
        std::string __name;
    public:
        OutOfBoundsEx(int, unsigned int);
        std::string getName() { return __name; };
        int getIncorrectData();
        friend std::ostream &operator<<(std::ostream &, const OutOfBoundsEx &);
    };

    class RemoveFromEmptyEx {
    private:
        unsigned int __clusterId;
        std::string __name;
    public:
        RemoveFromEmptyEx(std::string name, unsigned int);
        std::string getName() { return __name; };
        unsigned int getID() { return __clusterId; }
        friend std::ostream &operator<<(std::ostream &, const RemoveFromEmptyEx &);
    };
}


#endif //IP_PA4_EXCEPTIONS_H
