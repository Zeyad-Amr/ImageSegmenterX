#include "k-means.h"

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}

vector<int> find_closest_centroids(vector<vector<double>> X, vector<vector<double>> centroids) {
    // Set K
    int custerNo = centroids.size();

    // Initialize idx to all zeros
    vector<int> idx(X.size(), 0);

    // Loop over each example in X
    for (int i = 0; i < X.size(); i++) {
        double min_distance = 1e9;
        int closest_centroid_idx = 0;

        // Loop over each centroid
        for (int j = 0; j < custerNo; j++) {
            // Compute the Euclidean distance between the example and the centroid
            double distance = 0;
            for (int k = 0; k < X[i].size(); k++) {
                distance += pow(X[i][k] - centroids[j][k], 2);
            }
            distance = sqrt(distance);

            // Update the closest centroid if the distance is smaller
            if (distance < min_distance) {
                min_distance = distance;
                closest_centroid_idx = j;
            }
        }

        // Assign the closest centroid to the example
        idx[i] = closest_centroid_idx;
    }

    return idx;
}

vector<vector<double>> compute_centroids(vector<vector<double>> X, vector<int> idx, int K) {
    // Useful variables
    int m = X.size();
    int n = X[0].size();

    // Initialize centroids to all zeros
    vector<vector<double>> centroids(K, vector<double>(n, 0));
    vector<vector<double>> sumOfEachClusterPoints(K, vector<double>(n, 0));
    vector<int> countOfEachCluster(K, 0);

    // Loop over each example in X
    for (int i = 0; i < m; i++) {
        // Add the example to the sum of its assigned cluster points
        for (int j = 0; j < n; j++) {
            sumOfEachClusterPoints[idx[i]][j] += X[i][j];
        }

        // Increment the count of its assigned cluster
        countOfEachCluster[idx[i]]++;
    }

    // Compute the new centroids
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < n; j++) {
            if (countOfEachCluster[i] > 0) {
                centroids[i][j] = sumOfEachClusterPoints[i][j] / countOfEachCluster[i];
            }
        }
    }

    return centroids;
}
vector<vector<double>> run_kMeans(vector<vector<double>> X, vector<vector<double>> &initial_centroids,vector<int> &labels, int max_iters) {
    // Initialize values
    int m = X.size();
    int K = initial_centroids.size();
    vector<vector<double>> centroids = initial_centroids;
    vector<vector<double>> previous_centroids = centroids;
    labels = vector<int>(m, 0);

    // Run K-Means
    for (int i = 0; i < max_iters; i++) {
        // For each example in X, assign it to the closest centroid
        labels = find_closest_centroids(X, centroids);

        // Given the memberships, compute new centroids
        centroids = compute_centroids(X, labels, K);

        // Update previous centroids
        previous_centroids = centroids;
    }

    return centroids;
}
vector<vector<double>> kMeans_init_centroids(vector<vector<double>> X, int K) {
    // Randomly reorder the indices of examples
    std::srand(std::time(nullptr));
    random_shuffle(X.begin(), X.end());

    // Take the first K examples as centroids
    vector<vector<double>> centroids(K, vector<double>(X[0].size(), 0));
    for (int i = 0; i < K; i++) {
        centroids[i] = X[i];
    }

    return centroids;
}
void assignToClusters(vector<vector<double>> &vec,vector<int> labels,vector<vector<double>> centroids){
    for(int i=0;i<(int)vec.size();i++){
        vector<double> centroid = centroids[labels[i]];

        //convert the luv center to rgb
        int r,g,b;
        LUVtoRGB(centroid[0],centroid[1],centroid[2],r,g,b);
        vector<double> rgb;
        rgb.push_back(r);
        rgb.push_back(g);
        rgb.push_back(b);
        vec[i] = rgb;
    }
}
vector<vector<double>> convertMatToVector(cv::Mat image){
    vector<vector<double>> imageVector;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            vector<double> pixelColor;
            for(int k = 0;k<3;k++)
                pixelColor.push_back(pixel[k]);

            //convert rgb to luv
            float l,u,v;
            RGBtoLUV((int)pixelColor[0],(int)pixelColor[1],(int)pixelColor[2],l,u,v);
            pixelColor.clear();
            pixelColor.push_back(l);
            pixelColor.push_back(u);
            pixelColor.push_back(v);


            imageVector.push_back(pixelColor);
        }
    }
    return imageVector;
}

void processImageFromDataInVec(cv::Mat &image,vector<vector<double>> vec){
    int rows = image.rows;
    int cols = image.cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            vector<double> pixelColor;
            for(int k = 0;k<3;k++)
                pixel[k] = (int)vec[i*cols + j][k];
            image.at<cv::Vec3b>(i, j) = pixel;

        }
    }
}
void printCentroids(vector<vector<double>> centroids){
    int i = 0;
    for(auto centroid:centroids){
        i++;
        qDebug("%d", i);
        for(auto val:centroid){
            qDebug("%f ",val);
        }
        qDebug("\n");
    }
}
// Start Converting RGB TO LUV

void RGBtoLUV(int r, int g, int b, float& l, float& u, float& v) {
    cv::Mat rgb(1, 1, CV_8UC3, cv::Scalar(b, g, r));
    cv::Mat luv(1, 1, CV_8UC3);
    cv::cvtColor(rgb, luv, cv::COLOR_BGR2Luv);
    cv::Vec3b luvPixel = luv.at<cv::Vec3b>(0, 0);
    l = luvPixel[0];
    u = luvPixel[1];
    v = luvPixel[2];
}

//void RGBtoLUV(int r, int g, int b, float& l, float& u, float& v) {
//    float x, y, z, u0, v0, L;
//    float r_linear, g_linear, b_linear;
//
//    // Convert RGB values to linear RGB
//    float r_srgb = r / 255.0f;
//    float g_srgb = g / 255.0f;
//    float b_srgb = b / 255.0f;
//    if (r_srgb <= 0.04090f) {
//        r_linear = r_srgb / 12.92f;
//    } else {
//        r_linear = powf((r_srgb + 0.055f) / 1.055f, 2.4f);
//    }
//    if (g_srgb <= 0.04090f) {
//        g_linear = g_srgb / 12.92f;
//    } else {
//        g_linear = powf((g_srgb + 0.055f) / 1.055f, 2.4f);
//    }
//    if (b_srgb <= 0.04090f) {
//        b_linear = b_srgb / 12.92f;
//    } else {
//        b_linear = powf((b_srgb + 0.055f) / 1.055f, 2.4f);
//    }
//
//    // Convert linear RGB to XYZ
//    x = r_linear * 0.4124f + g_linear * 0.3576f + b_linear * 0.1805f;
//    y = r_linear * 0.2126f + g_linear * 0.7152f + b_linear * 0.0722f;
//    z = r_linear * 0.0193f + g_linear * 0.1192f + b_linear * 0.9505f;
//
//    // Convert XYZ to LUV
//    u0 = 4.0f * 0.95047f / (0.95047f + 15.0f + 3.0f * 1.08883f);
//    v0 = 9.0f / (0.95047f + 15.0f + 3.0f * 1.08883f);
//    L = y > 0.008856f ? 116.0f * powf(y, 1.0f/3.0f) - 16.0f : 903.3f * y;
//    u = 13.0f * L * (u0 * (4.0f * x / (x + 15.0f + 3.0f * 1.08883f)) - u0);
//    v = 13.0f * L * (v0 * (9.0f * y / (x + 15.0f + 3.0f * 1.08883f)) - v0);
//
//    // Assign LUV values to output parameters
//    l = L;
//}

// End Converting RGB to LUV


// Start Converting LUV to RGB
void LUVtoRGB(float l, float u, float v, int& r, int& g, int& b) {
    cv::Mat luv(1, 1, CV_8UC3, cv::Scalar(l, u, v));
    cv::Mat rgb(1, 1, CV_8UC3);
    cv::cvtColor(luv, rgb, cv::COLOR_Luv2BGR);
    cv::Vec3b rgbPixel = rgb.at<cv::Vec3b>(0, 0);
    b = rgbPixel[0];
    g = rgbPixel[1];
    r = rgbPixel[2];
}

void LUVtoRGB(float l, float u, float v, int& r, int& g, int& b) {
    float y, x, z;

    // Compute intermediate values
    float yVal = (l + 16.0) / 116.0;
    float uVal = u / 13.0 + 0.5;
    float vVal = v / 13.0 + 0.5;

    // Convert from LUV to XYZ
    if (l > 7.9996) {
        y = std::pow(yVal, 3.0);
    } else {
        y = (l / 903.3);
    }

    float a = (52.0 * l / (uVal + 13.0 * l * 0.1975) - 1.0) / 3.0;
    x = y * ((9.0 * a) / ((4.0 * vVal) - (a * 1.3333)));
    z = y * ((12.0 - (3.0 * a) - (20.0 * vVal)) / (4.0 * vVal));

    // Convert from XYZ to RGB
    float rFloat = x * 3.2406 - y * 1.5372 - z * 0.4986;
    float gFloat = -x * 0.9689 + y * 1.8758 + z * 0.0415;
    float bFloat = x * 0.0557 - y * 0.2040 + z * 1.0570;

    // Convert floating point values to integers
    r = std::round(rFloat * 255);
    g = std::round(gFloat * 255);
    b = std::round(bFloat * 255);

    // Ensure that the output RGB values are within the valid range of [0, 255]
    r = std::max(0, std::min(r, 255));
    g = std::max(0, std::min(g, 255));
    b = std::max(0, std::min(b, 255));
}

// End Converting LUV to RGB


void kMeansMainFunction(cv::Mat &image, int K)
{
    // Check if the image was loaded successfully
    if (image.empty()) {
        qDebug() << "Could not open or find the image";
        return;
    }
//    cv::Mat img = cv::imread("image.jpg");
//    cv::Mat img_luv;
//    cv::cvtColor(image, img_luv, cv::COLOR_BGR2Luv);

    vector<vector<double>> imageVector = convertMatToVector(image);
    vector<vector<double>> centroids = kMeans_init_centroids(imageVector,K);

    printCentroids(centroids);

    vector<int> labels;
    centroids = run_kMeans(imageVector,centroids,labels);

    printCentroids(centroids);

//    cv::Mat centers_rgb;
//    cv::cvtColor(centroids, centers_rgb, cv::COLOR_Luv2BGR);


    assignToClusters(imageVector,labels,centroids);
    processImageFromDataInVec(image,imageVector);

    printCentroids(centroids);

    // Display the image
    cv::imshow("Image", image);

    // Wait for a key press
    cv::waitKey(0);
}
