//
// Created by Adam on 11/6/2015.
//

#ifndef IP_PA4_KMEANS_H
#define IP_PA4_KMEANS_H

#include "Cluster.h"
#include "Point.h"

namespace Clustering {
    class KMeans {
    private:
        Cluster *__point_space;
        std::vector<Cluster> __clusterArray;
        unsigned int __k;
        unsigned int __d;
        std::vector<Point> __initCentroids;
    public:
        static constexpr double SCORE_DIFF_THRESHOLD = 0.001;
        KMeans();
        KMeans(int,int);
        ~KMeans();
        double computeClusteringScore();
    };
}

#include "KMeans.cpp"
#endif //IP_PA4_KMEANS_H
