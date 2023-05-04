//
// Created by Zeyad on 5/3/2023.
//

#include "mean_shift.h"



double mean_shift::linalgNorm(vector<double> arr1,vector<double> arr2){
    double norm = 0;
    for(int i=0;i<(int)arr1.size();i++){
        norm += pow((arr1[i]-arr2[i]),2);
    }
    return sqrt(norm);
}

//valid only for 2d feature data.
void mean_shift::showCentroids(Mat& image, vector<vector<double>>& centroids) {
    // Draw a red circle at each centroid location
    for (auto& centroid : centroids) {
        circle(image, Point(centroid[0], centroid[1]), 5, Scalar(0, 0, 255), -1);
    }

    // Display the image with centroids marked
    imshow("Centroids", image);
    waitKey(0);
}

// Assign a label to each feature set in X based on the nearest centroid
vector<int> mean_shift::getLabels(vector<vector<double>>& X, vector<vector<double>>& centroids) {
    vector<int> labels;
    for (auto& featureSet : X) {
        double mn = 1e9;
        int label = 0;
        for (int i = 0; i <(int) centroids.size(); i++) {
            double dist = linalgNorm(centroids[i],featureSet);
            if (dist < mn) {
                mn = dist;
                label = i;
            }
        }
        labels.push_back(label);
    }
    return labels;
}

// Compute the list of centroids of the clusters in X
vector<vector<double>> mean_shift::getCentroids(vector<vector<double>>& X, double radius, double threshold) {
    vector<vector<double>> centroids;
    set<int> visited;
    for (int i = 0; i < (int)X.size(); i++) {
        if (visited.find(i) == visited.end()) {
            vector<double> centroid = getFate(X, X[i], radius, threshold);
            centroids.push_back(centroid);

            for (int j = 0; j < (int)X.size(); j++) {
                if (linalgNorm(X[j], centroid) < radius) {
                    visited.insert(j);
                }
            }
        }
    }
    return centroids;
}

// Compute the fate of a point featureSet in X
vector<double> mean_shift::getFate(vector<vector<double>>& X, vector<double>& pointFeatureSet, double radius, double threshold) {
    vector<double> centroid = pointFeatureSet;
    while (true) {
        vector<vector<double>> in_bandWidth;
        vector<double> prevCentroid = centroid;
        for (auto& featureSet : X) {
            if (linalgNorm(featureSet,pointFeatureSet) < radius) {
                in_bandWidth.push_back(featureSet);
            }
        }

        if (in_bandWidth.empty()) {
            return centroid;
        }

        // Compute the new centroid as the mean of the feature sets in the bandwidth
        centroid = vector<double>(pointFeatureSet.size(),0);
        for (auto& featureSet : in_bandWidth) {
            for(int i =0;i<(int)featureSet.size();i++){
                centroid[i] += featureSet[i];
            }

        }
        for(int i =0;i<(int)centroid.size();i++){
            centroid[i] /= in_bandWidth.size();
        }

        if (linalgNorm(centroid,prevCentroid) < threshold) {
            return centroid;
        }
    }
}

void mean_shift::apply(Mat image,Mat& output, int radius)
{
    // Check if the image was loaded successfully
    if (image.empty()) {
        cout << "Could not open or find the image";
        return;
    }

    vector<vector<double>> imageVector = kmean().convertMatToVector(image);
    printf("converted image to vector");

    vector<vector<double>> centroids = getCentroids(imageVector,radius,radius);
    printf("got centroids");

    vector<int> labels = getLabels(imageVector,centroids);
    printf("finished getLabels");

    kmean().assignToClusters(imageVector,labels,centroids);
    printf("assigned to clusters");

    kmean().processImageFromDataInVec(image,imageVector);
    printf("processed image from vec");


    printf("%d\n",(int)centroids.size());
    kmean().printCentroids(centroids);


    output=image;
}
