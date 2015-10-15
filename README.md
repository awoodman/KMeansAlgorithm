# ucd-csi2312-pa2
Intermediate Programming - Programming Assignment 3

The first part of the code that will be described is the "Point Class", which is a class consisting of a point in space, with any number of dimensions.  Within the class, there are functions to do things like construct and destruct points, set a point equal to another point, subtract or add points, multiply or divide a point by a number, etc.  Any new points in space should, in general, be created using the point class.  

Next, a cluster class was created, which is meant to contain point objects.  The cluster class allows us to do things like add points, subtract points, add clusters to clusters, subtract clusters from clusters, etc.  Every point in the cluster(s) are stored in lexicographic order.  All points in a cluster must have the same amount of dimensions.  

Next, a KMeans algorithm was written.  The algorithm begins with the user choosing a number or clusters, to encompass the data in.  Based on this, the data is put into a correct cluster based off of its distance from the clusters "centroid".  The centroid is calculated based off of the points in the cluster (an average of).
