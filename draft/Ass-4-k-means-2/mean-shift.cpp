#include "mean-shift.h"


double linalgNorm(std::vector<double> arr1,std::vector<double> arr2){
    double norm = 0;
    for(int i=0;i<(int)arr1.size();i++){
        norm += pow((arr1[i]-arr2[i]),2);
    }
    return sqrt(norm);
}

void showCentroids(cv::Mat& image, std::vector<std::vector<double>>& centroids) {
    // Draw a red circle at each centroid location
    for (auto& centroid : centroids) {
        cv::circle(image, cv::Point(centroid[0], centroid[1]), 5, cv::Scalar(0, 0, 255), -1);
    }

    // Display the image with centroids marked
    cv::imshow("Centroids", image);
    cv::waitKey(0);
}

// Assign a label to each feature set in X based on the nearest centroid
std::vector<int> getLabels(std::vector<std::vector<double>>& X, std::vector<std::vector<double>>& centroids) {
    std::vector<int> labels;
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
std::vector<std::vector<double>> getCentroids(std::vector<std::vector<double>>& X, double radius, double threshold) {
    std::vector<std::vector<double>> centroids;
    std::set<int> visited;
    for (int i = 0; i < (int)X.size(); i++) {
        if (visited.find(i) == visited.end()) {
            std::vector<double> centroid = getFate(X, X[i], radius, threshold);
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
std::vector<double> getFate(std::vector<std::vector<double>>& X, std::vector<double>& pointFeatureSet, double radius, double threshold) {
    std::vector<double> centroid = pointFeatureSet;
    while (true) {
        std::vector<std::vector<double>> in_bandWidth;
        std::vector<double> prevCentroid = centroid;
        for (auto& featureSet : X) {
            if (linalgNorm(featureSet,pointFeatureSet) < radius) {
                in_bandWidth.push_back(featureSet);
            }
        }

        if (in_bandWidth.empty()) {
            return centroid;
        }

        // Compute the new centroid as the mean of the feature sets in the bandwidth
        centroid = std::vector<double>(pointFeatureSet.size(),0);
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

void meanShiftMainFunction(cv::Mat &image, int radius)
{
    // Check if the image was loaded successfully
    if (image.empty()) {
        qDebug() << "Could not open or find the image";
        return;
    }

    vector<vector<double>> imageVector = convertMatToVector(image);
    qDebug("converted image to vector");

    vector<vector<double>> centroids = getCentroids(imageVector,radius,radius);
    qDebug("got centroids");

    vector<int> labels = getLabels(imageVector,centroids);
    qDebug("finished getLabels");

    assignToClusters(imageVector,labels,centroids);
    qDebug("assigned to clusters");

    processImageFromDataInVec(image,imageVector);
    qDebug("processed image from vec");


    qDebug("%d\n",(int)centroids.size());
    printCentroids(centroids);


    // Display the image
    cv::imshow("Image", image);

    // Wait for a key press
    cv::waitKey(0);
}
