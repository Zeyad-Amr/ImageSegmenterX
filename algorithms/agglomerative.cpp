#include "agglomerative.h"

double agglomerative::euclidean_distance(const std::vector<double> &point1, const std::vector<double> &point2)
{
    if (point1.size() != point2.size())
    {
        throw invalid_argument("Point dimensions do not match");
    }
    double sum = 0.0;
    for (size_t i = 0; i < point1.size(); ++i)
    {
        double diff = point1[i] - point2[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

double agglomerative::clusters_distance(const vector<vector<double>> &cluster1,
                                        const vector<vector<double>> &cluster2)
{
    double max_dist = 0.0;
    for (const auto &point1 : cluster1)
    {
        for (const auto &point2 : cluster2)
        {
            double dist = euclidean_distance(point1, point2);
            if (dist > max_dist)
            {
                max_dist = dist;
            }
        }
    }
    return max_dist;
}

vector<vector<vector<double>>> agglomerative::initial_clusters(Mat img_matrix)
{
    vector<vector<vector<double>>> clusters;
    vector<double> results;
    int initial_k = 20;
    vector<vector<vector<double>>> groups(initial_k);

    int d = static_cast<int>(256 / initial_k);

    for (int i = 0; i < img_matrix.rows; i++)
    {
        vector<double> matrix_value_point = img_matrix.row(i);

        for (int j = 0; j < initial_k; j++)
        {
            double k = j * d;
            vector<double> color_value_point = {k, k, k};
            double result = euclidean_distance(matrix_value_point, color_value_point);
            results.push_back(result);
        }

        auto it = std::min_element(results.begin(), results.end());

        int index = std::distance(results.begin(), it);
        groups[index].push_back(matrix_value_point);

        results.clear();
    }

    for (const auto &group : groups)
    {
        if (!group.empty())
        {
            vector<vector<double>> point_group;
            for (const auto &point : group)
            {
                point_group.push_back(point);
            }
            clusters.push_back(point_group);
        }
    }

    return clusters;
}

void agglomerative::fit(int k, Mat &img, vector<int> &labels, map<int, vector<double>> &centers, map<vector<double>, int> &cluster_map)
{
    // Initialize clusters
    vector<vector<vector<double>>> clusters = initial_clusters(img);

    while (clusters.size() > k)
    {
        vector<vector<double>> cluster1, cluster2;
        double min_distance = DBL_MAX;

        for (int i = 0; i < clusters.size(); ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                double distance = clusters_distance(clusters[i], clusters[j]);

                if (distance < min_distance)
                {
                    min_distance = distance;
                    cluster1 = clusters[i];
                    cluster2 = clusters[j];
                }
            }
        }

        clusters.erase(std::remove(clusters.begin(), clusters.end(), cluster1), clusters.end());
        clusters.erase(std::remove(clusters.begin(), clusters.end(), cluster2), clusters.end());

        vector<vector<double>> merged_cluster = cluster1;
        merged_cluster.insert(merged_cluster.end(), cluster2.begin(), cluster2.end());

        clusters.push_back(merged_cluster);
    }

    cluster_map.clear();
    for (int i = 0; i < clusters.size(); ++i)
    {
        for (int j = 0; j < clusters[i].size(); ++j)
        {
            cluster_map[clusters[i][j]] = i;
        }
    }

    // Compute cluster centers
    centers.clear();
    for (int i = 0; i < clusters.size(); ++i)
    {
        Mat cluster_img(clusters[i].size(), clusters[i][0].size(), CV_64FC1);

        for (int j = 0; j < clusters[i].size(); ++j)
        {
            for (int k = 0; k < clusters[i][j].size(); ++k)
            {
                cluster_img.at<double>(j, k) = clusters[i][j][k];
            }
        }

        Mat center_img;
        reduce(cluster_img, center_img, 0, REDUCE_AVG);

        vector<double> center;
        for (int j = 0; j < center_img.cols; ++j)
        {
            center.push_back(center_img.at<double>(0, j));
        }
        centers[i] = center;
    }

    labels.clear();
    for (int i = 0; i < img.rows; ++i)
    {
        vector<double> pixel = img.row(i);
        int cluster_num = cluster_map[pixel];
        labels.push_back(cluster_num);
    }
}

// Function to predict the cluster that a given point belongs to (returns cluster number)
int agglomerative::predict_cluster(map<vector<double>, int> &cluster_map, vector<double> &point)
{
    return cluster_map[point];
}

// Function to predict the center of the cluster that a given point belongs to (returns center coordinates)
vector<double> agglomerative::predict_center(map<int, vector<double>> &centers, map<vector<double>, int> &cluster_map, vector<double> &point)
{
    // Predict the cluster that the point belongs to and return the center of that cluster (center coordinates)
    int point_cluster_num = predict_cluster(cluster_map, point);
    vector<double> center = centers[point_cluster_num];
    return center;
}

std::pair<Mat, Mat> agglomerative::adjust(Mat &image)
{
    Mat resized;
    Mat img;
    resize(image, resized, Size(300, 300));
    img = resized.reshape(1, resized.rows * resized.cols);
    return {img, resized};
}

Mat agglomerative::segmentation(int k, Mat &img, Mat &resized)
{

    // Fit the model to the data
    vector<int> labels;
    map<int, vector<double>> centers;
    map<vector<double>, int> cluster_map;
    fit(k, img, labels, centers, cluster_map);

    // Segment the image
    Mat output(resized.size(), resized.type());
    for (int i = 0; i < resized.rows; ++i)
    {
        for (int j = 0; j < resized.cols; ++j)
        {
            Vec3b pixel = resized.at<Vec3b>(i, j);
            vector<double> point = {(double)pixel[0], (double)pixel[1], (double)pixel[2]};
            vector<double> center = predict_center(centers, cluster_map, point);
            Vec3b new_pixel(center[0], center[1], center[2]);
            output.at<Vec3b>(i, j) = new_pixel;
        }
    }
    return output;
}
