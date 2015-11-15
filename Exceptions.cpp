//
// Created by Adam on 11/14/2015.
//

#include "Exceptions.h"

namespace Clustering {

    DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int correctDim, unsigned int incorrectDim) {
        __correctDim = correctDim;
        __incorrectDim = incorrectDim;
        __name = "DimensionalityMismatchEx";
    }

    std::ostream &operator<<(std::ostream &os, const DimensionalityMismatchEx &DimMisEx) {
        os << DimMisEx.__name << ": Correct Dimension = " << DimMisEx.__correctDim;
        os << ", Incorrect Dimension Attempted = " << DimMisEx.__incorrectDim << std::endl;
    }


    OutOfBoundsEx::OutOfBoundsEx(int incIndex, unsigned int maxIndex) {
        __incorrectIndex = incIndex;
        __maxIndex = maxIndex;
        __minIndex = 0;
        __name = "OutOfBoundsEx";
    }

    std::ostream &operator<<(std::ostream &os, const OutOfBoundsEx &OutBdsEx) {
        os << OutBdsEx.__name << ": Min Index Possible = " << OutBdsEx.__minIndex;
        os << ", Max Index Possible = " << OutBdsEx.__maxIndex;
        os << ", Incorrect Index Passed = " << OutBdsEx.__incorrectIndex << std::endl;
    }


    RemoveFromEmptyEx::RemoveFromEmptyEx(std::string name, unsigned int clusterId) {
        __name = name;
        __clusterId = clusterId;
    }

    std::ostream &operator<<(std::ostream &os, const RemoveFromEmptyEx &RemEmpEx) {
        os << RemEmpEx.__name << ": ID = " << RemEmpEx.__clusterId << std::endl;
    }

}