//
// Created by Adam on 11/6/2015.
//
#include <fstream>

#include "KMeans.h"

namespace Clustering {
    template <typename T, int k, int dim>
    KMeans<T,k,dim>::KMeans() : __k(k), __d(dim)
    {
        // Set member variables
        double score = 0, prevScore;
        double scoreDiff = SCORE_DIFF_THRESHOLD + 1;

        // Initializing Algorithm
        std::ifstream csv("points.txt");
        __point_space = new Cluster<T,dim>;
        __point_space->setDimensionality(__d);
        csv >> *__point_space;
        csv.close();
        cout << "Max Map Size: " << __point_space->maxMapSize() << endl;
        int numDist = (__point_space->getSize())*(__point_space->getSize()-1)/2;
        cout << "Number Distances to Store: " << numDist << endl;
        cout << "------------------------------------------" << endl;
        if (__k <= __point_space->getSize()) {
            __point_space->pickPoints(__k, __initCentroids);
            __point_space->setCentroid(__initCentroids[0]); // set point_space cluster's centroid as first entry in initCent.
            __point_space->preAllocMap(numDist);

            __clusterArray.push_back(*__point_space);              // put original pointspace cluster into array
            delete __point_space;
            for (int i = 1; i < __k; i++)                 // populate the cluster array
            {
                Cluster<T,dim> *newCluster = new Cluster<T,dim>;
                newCluster->setDimensionality(__d);
                newCluster->setCentroid(__initCentroids[i]);
                newCluster->validCentroid();
                __clusterArray.push_back(*newCluster);
                delete newCluster;
            }

//        KMeans Algorithm
            while (scoreDiff > SCORE_DIFF_THRESHOLD)            // loop until diff < diffThreshold
            {
                static int iter = 0;
                for (int i = 0; i < __k; i++)                     // loop thru all clusters
                {
                    for (int j = 0; j < __clusterArray[i].getSize(); j++)         // loop thru all points in cluster
                    {
                        T point = __clusterArray[i].getPoint(j);  // get point for comparisons
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
                            typename Cluster<T,dim>::Move(point, &__clusterArray[i], &__clusterArray[closestCentInd]).perform();
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
                std::cout << "Max Map Size: " << __point_space->maxMapSize() << endl;
                std::cout << "Current Map Size: " << __point_space->getMapSize() << std::endl;
                std::cout << "------------------------------" << std::endl;
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
            delete __point_space;
        }
    }


    template <typename T, int k, int dim>
    KMeans<T,k,dim>::~KMeans()
    {
//        auto it = __clusterArray.begin();
//        auto last_it = it;
//        for (int i = 0; i < __k; i++)
//            last_it = it;
//            it++;
//            delete last_it;
    }

    template <typename T, int k, int dim>
    double KMeans<T,k,dim>::computeClusteringScore()
    {
        double BetaCV = 0, Din = 0, Dout = 0;

        // Compute Din
        for (int i = 0; i < __k; i++)
        {
            Din = Din + __clusterArray[i].intraClusterDistance();
        }

        // Compute Dout
        for (int j = 0; j < (__k - 1); j++)
        {
            for (int l = (j + 1); l < __k; l++)
            {
                if (j != l) {                           // Don't add distance between itself
                    Dout = Dout + interClusterDistance(__clusterArray[l],__clusterArray[j]);
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
        for (int n = 0; n < (__k - 1); n++)
        {
            for (int o = (n + 1); o < __k; o++)
            {
                Pout = Pout + interClusterEdges(__clusterArray[n],__clusterArray[o]);
            }
        }

        BetaCV = (Din / Pin) / (Dout / Pout);

        return BetaCV;
    }

}