//
// Created by Adam on 10/8/2015.
//

#include "KMeans.h"
#include <fstream>
#include <cmath>

namespace Clustering {

    KMeans::KMeans()
    {
        // Set member variables
        k = 5;                          // Arbitrary # of clusters
        double score, prevScore;
        double scoreDiff = SCORE_DIFF_THRESHOLD + 1;

        // Initializing Algorithm
        std::ifstream csv("points.txt");
        Cluster* pointSpace = new Cluster;
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
            newCluster->validCentroid();
            clusterArray[i] = newCluster;
        }

//        KMeans Algorithm
        while (scoreDiff > SCORE_DIFF_THRESHOLD)            // loop until diff < diffThreshold
        {
            static int iter = 0;
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

            prevScore = score;

            // Compute new Clustering Score
            score = computeClusteringScore();

            scoreDiff = fabs(score - prevScore);

            std::cout << "Iteration: " << ++iter << std::endl;
            std::cout << "Score: " << score << std::endl;
        }

        // Print all clusters
        std::ofstream outfile("output.txt");
        for (int i = 0; i < k; i++)
        {
            outfile << *clusterArray[i];
        }
        outfile.close();


        // Clean up memory
        for (int n = 0; n < k; n++)
        {
            int size = clusterArray[n]->getSize();

            for (int i = 0; i < size; i++) {
                delete clusterArray[n]->getPoint(i);    // delete all points in each cluster
            }

            //TODO: delete nodes within cluster

            delete clusterArray[n];     // delete 'k' dynamic clusters
        }
        delete [] clusterArray;            // delete dynamic cluster array
    }


    double KMeans::computeClusteringScore()
    {
        double BetaCV = 0, Din = 0, Dout = 0;

        // Compute Din
        for (int i = 0; i < k; i++)
        {
            Din = Din + clusterArray[i]->intraClusterDistance();
        }

        // Compute Dout
        for (int j = 0; j < k; j++)
        {
            for (int l = 0; l < k; l++)
            {
                if (j != l) {                           // Don't add distance between itself
                    Cluster c1 = *clusterArray[l];
                    Cluster c2 = *clusterArray[j];
                    Dout = Dout + interClusterDistance(c1, c2);
                }
            }
        }

        // Compute Pin
        int Pin = 0;
        for (int m = 0; m < k; m++)
        {
            Pin = Pin + clusterArray[m]->getClusterEdges();
        }

        // Compute Pout
        int Pout = 0;
        for (int n = 0; n < k; n++)
        {
            for (int o = n + 1; o < (k - 1); o++)
            {
                Pout = Pout + interClusterEdges(*clusterArray[n],*clusterArray[o]);
            }
        }

        BetaCV = (Din / Pin) / (Dout / Pout);

        return BetaCV;
    }
}