//
// Created by Adam on 11/6/2015.
//

#ifndef IP_PA4_KMEANS_H
#define IP_PA4_KMEANS_H

#include "Cluster.h"
#include "Point.h"

namespace Clustering {

    template <typename T, int k, int dim>
    class KMeans {
    private:
        Cluster<T,dim>*__point_space;
        std::vector<Cluster<T,dim>> __clusterArray;
        int __k;
        int __d;
        std::vector<T> __initCentroids;
    public:
        static constexpr double SCORE_DIFF_THRESHOLD = 0.001;
        KMeans();
        ~KMeans();
        double computeClusteringScore();
//        void preAllocSpace(Cluster<T,dim> &, int);
    };
}

#include "KMeans.cpp"
#endif //IP_PA4_KMEANS_H
