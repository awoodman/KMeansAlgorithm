//
// Created by Adam on 11/6/2015.
//

#include "KMeans.h"
#include <fstream>

namespace Clustering {
    template <int k, int dim>
    KMeans<k,dim>::KMeans() : __k(k), __d(dim)
    {
        // Set member variables
        double score, prevScore;
        double scoreDiff = SCORE_DIFF_THRESHOLD + 1;

        // Initializing Algorithm
        std::ifstream csv("points.txt");
        __point_space = new Cluster<Point<dataType,dim>,dim>;
        __point_space->setDimensionality(__d);
        csv >> *__point_space;
        if (__k <= __point_space->getSize()) {
            __point_space->pickPoints(__k, __initCentroids);
            __point_space->setCentroid(__initCentroids[0]); // set point_space cluster's centroid as first entry in initCent.

            __clusterArray.push_back(*__point_space);              // put original pointspace cluster into array
            for (int i = 1; i < __k; i++)                 // populate the cluster array
            {
                Cluster<Point<dataType,dim>,dim> *newCluster = new Cluster<Point<dataType,dim>,dim>;
                newCluster->setDimensionality(__d);
                newCluster->setCentroid(__initCentroids[i]);
                newCluster->validCentroid();
                __clusterArray.push_back(*newCluster);
            }

//        KMeans Algorithm
            while (scoreDiff > SCORE_DIFF_THRESHOLD)            // loop until diff < diffThreshold
            {
                static int iter = 0;
                for (int i = 0; i < __k; i++)                     // loop thru all clusters
                {
                    for (int j = 0; j < __clusterArray[i].getSize(); j++)         // loop thru all points in cluster
                    {
                        Point<dataType,dim> point = __clusterArray[i].getPoint(j);  // get point for comparisons
                        double closestCentDist = point.distanceTo(__clusterArray[i].getCentroid());
                        int closestCentInd = i;
                        for (int l = 0; l < __k; l++)             // loop thru every centroid to compare w point
                        {
                            if (i != l) {
                                double otherCentDist = point.distanceTo(__clusterArray[l].getCentroid());
                                if (closestCentDist > otherCentDist) {
                                    closestCentDist = otherCentDist;
                                    closestCentInd = l;
                                }
                            }
                        }
                        if (closestCentInd != i) {
                            Cluster<Point<dataType,dim>,dim>::Move(point, &__clusterArray[i], &__clusterArray[closestCentInd]).perform();
                        }
                    }
                }

                for (int m = 0; m < __k; m++)                     // loop thru all clusters to recompute centroid
                {
                    if (!(__clusterArray[m].validCentroid()))
                        __clusterArray[m].computeCentroid();
                }

                prevScore = score;

                // Compute new Clustering Score
                score = computeClusteringScore();

                scoreDiff = fabs(score - prevScore);

                std::cout << "Iteration: " << ++iter << std::endl;
                std::cout << "Score: " << score << std::endl;
                std::cout << "ScoreDiff: " << scoreDiff << std::endl;
            }

            // Print all clusters
            std::ofstream outfile("output.txt");
            for (int i = 0; i < __k; i++) {
                outfile << __clusterArray[i];
            }
            outfile.close();
        }
        else
        {
            std::cout << "You are asking for more clusters than you have points! Program Terminating." << std::endl;
        }
    }


    template <int k, int dim>
    KMeans<k,dim>::~KMeans()
    {
//        // Clean up memory
//        for (int n = 0; n < __k; n++)
//        {
//            int size = __clusterArray[n].getSize();
//
//            for (int i = 0; i < size; i++) {
//                delete __clusterArray[n][i];    // delete all points in each cluster
//            }
//
//            delete __clusterArray[n];     // delete 'k' dynamic clusters
//        }
//        delete [] clusterArray;            // delete dynamic cluster array
    }

    template <int k, int dim>
    double KMeans<k,dim>::computeClusteringScore()
    {
        double BetaCV = 0, Din = 0, Dout = 0;

        // Compute Din
        for (int i = 0; i < __k; i++)
        {
            Din = Din + __clusterArray[i].intraClusterDistance();
        }

        // Compute Dout
        for (int j = 0; j < __k; j++)
        {
            for (int l = 0; l < __k; l++)
            {
                if (j != l) {                           // Don't add distance between itself
                    Cluster<Point<dataType,dim>,dim> c1 = __clusterArray[l];
                    Cluster<Point<dataType,dim>,dim> c2 = __clusterArray[j];
                    Dout = Dout + interClusterDistance(c1, c2);
                }
            }
        }

        // Compute Pin
        int Pin = 0;
        for (int m = 0; m < __k; m++)
        {
            Pin = Pin + __clusterArray[m].getClusterEdges();
        }

        // Compute Pout
        int Pout = 0;
        for (int n = 0; n < __k; n++)
        {
            for (int o = n + 1; o < (__k - 1); o++)
            {
                Pout = Pout + interClusterEdges(__clusterArray[n],__clusterArray[o]);
            }
        }

        BetaCV = (Din / Pin) / (Dout / Pout);

        return BetaCV;
    }
}