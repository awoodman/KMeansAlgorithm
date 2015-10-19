//
// Created by Adam on 10/8/2015.
//

#ifndef PA2_IP_KMEANS_H
#define PA2_IP_KMEANS_H

#include "Cluster.h"
#include "Point.h"

namespace Clustering {
    class KMeans {
    private:
        Cluster* point_space;
        Cluster** clusterArray;
        int k;                                // Number of Clusters
        PointPtr *initCentroids;                  // Initial centroid array (to be populated w. pickPoints)
    public:
        static constexpr double SCORE_DIFF_THRESHOLD = 0.1;         // Termination condition for outer loop of iterative algorithm

        KMeans();                                   // Default Constructor

        double computeClusteringScore();
    };
}

#endif //PA2_IP_KMEANS_H
