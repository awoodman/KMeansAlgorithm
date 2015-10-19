//
// Created by Adam on 10/8/2015.
//

#include "KMeans.h"
#include "Point.h"
#include "Cluster.h"
#include <fstream>

namespace Clustering {

    KMeans::KMeans()
    {
        // Set member variables
        k = 5;                          // Arbitrary # of clusters
        double score;
        double scoreDiff = SCORE_DIFF_THRESHOLD + 1;

        // Initializing Algorithm
        std::ifstream csv("points.txt");
        Cluster* pointSpace = new Cluster;
        pointSpace->rpTrue();
        csv >> *pointSpace;
        point_space = pointSpace;
        initCentroids = new PointPtr[k];
        for (int i = 0; i < k; i++)
            initCentroids[i] = nullptr;             // set all array values to null, mainly for testing purposes
        point_space->pickPoints(k,initCentroids);
        point_space->setCentroid(*initCentroids[0]); // set point_space cluster's centroid as first entry in initCent.

        clusterArray = new Cluster*[k];             // Create dynamic array of ClusterPtrs

        clusterArray[0] = point_space;              // put original pointspace cluster into array
        for (int i = 1; i < k; i++)                 // populate the cluster array
        {
            Cluster* newCluster = new Cluster;
            newCluster->setCentroid(*initCentroids[i]);
            newCluster->rpFalse();                  // set release points to false
            newCluster->validCentroid();
            clusterArray[i] = newCluster;
        }

//        KMeans Algorithm
//        while (scoreDiff > SCORE_DIFF_THRESHOLD)            // loop until diff < diffThreshold
        for (int i = 0; i < 50; i++) // TODO: change to the above while condition
        {
            for (int i = 0; i < k; i++)                     // loop thru all clusters
            {
                int clustSize = clusterArray[i]->getSize();
                for (int j = 0; j < clustSize; j++)         // loop thru all points in cluster
                {
                    PointPtr point = clusterArray[i]->getPoint(j);  // get point for comparisons
                    double closestCentDist = point->distanceTo(clusterArray[i]->getCentroid()); // distance to points current centroid
                    int closestCentInd = i;
                    for (int l = 0; l < k; l++)             // loop thru every centroid to compare w point
                    {
                        double otherCentDist = point->distanceTo(clusterArray[l]->getCentroid());
                        if (closestCentDist > otherCentDist) {
                            closestCentDist = otherCentDist;
                            closestCentInd = l;
                        }
                    }
                    if (closestCentInd != i) {
                        Cluster::Move(point, clusterArray[i], clusterArray[closestCentInd]).perform();
                        clustSize--;
                    }
                }
            }
            for (int m = 0; m < k; m++)                     // loop thru all clusters to recompute centroid
            {
                if (!(clusterArray[m]->validCentroid()))
                    clusterArray[m]->computeCentroid();
            }
        }

        // Print all clusters
        std::ofstream outfile("output.txt");
        for (int i = 0; i < k; i++)
        {
            outfile << *clusterArray[i];
        }
        outfile.close();

    }

    double KMeans::computeClusteringScore()
    {

    }
}