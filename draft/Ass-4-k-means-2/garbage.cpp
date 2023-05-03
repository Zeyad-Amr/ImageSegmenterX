


//const double threshold = 4;
//const double radius = 4;

// Compute the fate of a point featureSet in X
//std::vector<double> getFate(std::vector<std::vector<double>>& X, std::vector<double>& pointFeatureSet) {
//    std::vector<double> centroid = pointFeatureSet;
//    while (true) {
//        std::vector<std::vector<double>> in_bandWidth;
//        std::vector<double> prevCentroid = centroid;
//        for (auto& featureSet : X) {
//            if (linalgNorm(featureSet,pointFeatureSet) < radius) {
//                in_bandWidth.push_back(featureSet);
//            }
//        }

//        if (in_bandWidth.empty()) {
//            return centroid;
//        }

//        // Compute the new centroid as the mean of the feature sets in the bandwidth
//        centroid = std::vector<double>(pointFeatureSet.size(),0);
//        for (auto& featureSet : in_bandWidth) {
//            for(int i =0;i<(int)featureSet.size();i++){
//                centroid[i] += featureSet[i];
//            }

//        }
//        for(int i =0;i<(int)centroid.size();i++){
//            centroid[i] /= in_bandWidth.size();
//        }

//        if (linalgNorm(centroid,prevCentroid) < threshold) {
//            return centroid;
//        }
//    }
//}

//// Compute the list of centroids of the clusters in X
//std::vector<std::vector<double>> getCentroids(std::vector<std::vector<double>>& X,double radius,double threshold) {
//    std::vector<std::vector<double>> centroids;
//    for (auto& featureSet : X) {
//        std::vector<double> centroid = getFate(X, featureSet);


//        bool nearbyToKnown = false;
//        for (auto& centroid_ : centroids) {
//            if (linalgNorm(centroid,centroid_) < threshold) {
//                nearbyToKnown = true;
//                break;
//            }
//        }
//        if (!nearbyToKnown) {
//            centroids.push_back(centroid);
//        }
//    }
//    return centroids;
//}

//// Assign a label to each feature set in X based on the nearest centroid
//std::vector<int> getLabels(std::vector<std::vector<double>>& X,std::vector<std::vector<double>> centroids) {
////    std::vector<std::vector<double>> centroids = getCentroids(X);
//    std::vector<int> labels;
//    for (auto& featureSet : X) {
////        std::vector<double> fate = getFate(X, featureSet);
//        std::vector<double> fate = featureSet;

//        double mn = 1e9;
//        int label = 0;
//        for (int i = 0; i < (int)centroids.size(); i++) {
//            double dist = linalgNorm(centroids[i],fate);
//            if (dist < mn) {
//                mn = dist;
//                label = i;
//            }
//        }
//        labels.push_back(label);
//    }
//    return labels;
//}




//#include <opencv2/opencv.hpp>

//std::vector<std::vector<double>> centroids = getCentroids(imageVector, radius, threshold);
//std::vector<int> labels = getLabels(imageVector, centroids);




//void RGBtoLUV(int R, int G, int B, float& L, float& U, float& V) {
//    // Convert RGB to XYZ
//    double r = R / 255.0;
//    double g = G / 255.0;
//    double b = B / 255.0;
//    double x = 0.412453*r + 0.357580*g + 0.180423*b;
//    double y = 0.212671*r + 0.715160*g + 0.072169*b;
//    double z = 0.019334*r + 0.119193*g + 0.950227*b;

//    // Convert XYZ to LUV
//    double yr = y / 1.0;
//    double ur = (4.0 * x) / (x + (15.0 * y) + (3.0 * z));
//    double vr = (9.0 * y) / (x + (15.0 * y) + (3.0 * z));

//    double L1 = 0.0, U1 = 0.0, V1 = 0.0;

//    if (yr > 0.008856) {
//        L1 = 116.0 * pow(yr, 1.0/3.0) - 16.0;
//    } else {
//        L1 = 903.3 * yr;
//    }

//    U1 = 13.0 * L1 * (ur - 0.19793943);
//    V1 = 13.0 * L1 * (vr - 0.46831096);

//    // Set output values
//    L = L1;
//    U = U1;
//    V = V1;
//}
//#include <cmath>

//void rgb_to_xyz(float r, float g, float b, float& x, float& y, float& z) {
//    r /= 255.0;
//    g /= 255.0;
//    b /= 255.0;

//    if (r > 0.04045) {
//        r = std::pow((r + 0.055) / 1.055, 2.4);
//    } else {
//        r /= 12.92;
//    }

//    if (g > 0.04045) {
//        g = std::pow((g + 0.055) / 1.055, 2.4);
//    } else {
//        g /= 12.92;
//    }

//    if (b > 0.04045) {
//        b = std::pow((b + 0.055) / 1.055, 2.4);
//    } else {
//        b /= 12.92;
//    }

//    r *= 100.0;
//    g *= 100.0;
//    b *= 100.0;

//    x = 0.412453 * r + 0.357580 * g + 0.180423 * b;
//    y = 0.212671 * r + 0.715160 * g + 0.072169 * b;
//    z = 0.019334 * r + 0.119193 * g + 0.950227 * b;
//}

//void xyz_to_luv(float x, float y, float z, float& l, float& u, float& v) {
//    float x_n = 0.95047;  // Observer= 2°, Illuminant= D65
//    float y_n = 1.0;
//    float z_n = 1.08883;
//    float t = y / y_n;

//    if (t > 0.008856) {
//        l = 116 * std::pow(t, 1/3.0) - 16;
//    } else {
//        l = 903.3 * t;
//    }

//    float d = x + 15 * y + 3 * z;
//    float u_prime = 4 * x / d;
//    float v_prime = 9 * y / d;

//    float u_n = 4 * x_n / (x_n + 15 * y_n + 3 * z_n);
//    float v_n = 9 * y_n / (x_n + 15 * y_n + 3 * z_n);

//    u = 13 * l * (u_prime - u_n);
//    v = 13 * l * (v_prime - v_n);
//}

//void rgb_to_luv(float r, float g, float b, float& l, float& u, float& v) {
//    float x, y, z;
//    rgb_to_xyz(r, g, b, x, y, z);
//    xyz_to_luv(x, y, z, l, u, v);
//}
