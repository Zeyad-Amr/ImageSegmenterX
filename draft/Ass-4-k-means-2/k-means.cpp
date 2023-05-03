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
void RGBtoLUV(int r, int g, int b, float& l, float& u, float& v) {
    cv::Mat rgb(1, 1, CV_8UC3, cv::Scalar(b, g, r));
    cv::Mat luv(1, 1, CV_8UC3);
    cv::cvtColor(rgb, luv, cv::COLOR_BGR2Luv);
    cv::Vec3b luvPixel = luv.at<cv::Vec3b>(0, 0);
    l = luvPixel[0];
    u = luvPixel[1];
    v = luvPixel[2];
}

void LUVtoRGB(float l, float u, float v, int& r, int& g, int& b) {
    cv::Mat luv(1, 1, CV_8UC3, cv::Scalar(l, u, v));
    cv::Mat rgb(1, 1, CV_8UC3);
    cv::cvtColor(luv, rgb, cv::COLOR_Luv2BGR);
    cv::Vec3b rgbPixel = rgb.at<cv::Vec3b>(0, 0);
    b = rgbPixel[0];
    g = rgbPixel[1];
    r = rgbPixel[2];
}


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
