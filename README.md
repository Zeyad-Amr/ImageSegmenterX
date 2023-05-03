<h1 align="center">
 <strong>Task 4 cv</strong>
 <br/><br/>
</h1>

## Table of Contents

- [Introduction](#introduction)
- [Technologies](#technologies)
- [How to Use](#how-to-use)
- [Features](#features)
- [Harris operator](#harris-operator)
- [SIFT](#sift)
- [Matching the images](#matching-the-images)
- [SSD](#ssd)
- [NCC](#ncc)
- [Contributing](#contributing)
- [Developers](#developers)

## Introduction
It’s a desktop application that aims to involve analyzing images to extract information and identify unique features. In this context, the Harris operator is a widely used algorithm for feature detection, which highlights areas of high contrast in an image. By using Harris operator and λ, we can extract unique features from all images.

To further process these features, the Scale-Invariant Feature Transform (SIFT) algorithm is used to generate feature descriptors that are invariant to scale, rotation, and illumination changes. These descriptors are used to identify key points in an image that can be used for matching.

Matching the features across multiple images is done using techniques such as Sum of Squared Differences (SSD) and Normalized Cross Correlations. These techniques measure the similarity between pairs of features in different images and help to identify correspondences between them.


## Technologies
- Desktop application using : qt, cpp
- Processing: cpp, opencv


## How to Use

1. Clone the repository using the command `git clone https://github.com/Zeyad-Amr/Photostudio`


# Features
## Harris operator :

The Harris corner detector is a popular algorithm used for detecting and extracting unique features in an image. It is based on the assumption that a corner in an image is a region of the image where the gradient vector has a significant change in both directions. The Harris operator uses a mathematical formula to detect such regions.

To extract unique features in all images using Harris operator and λ, we can follow the following steps:

1. Convert the images to grayscale: The Harris operator works on grayscale images. Therefore, we need to convert the images to grayscale.

2. Compute the image gradient: Compute the gradient of the image in both the x and y directions. This can be done using edge detection filters such as Sobel, Prewitt, or Roberts.

3. Compute the Harris response: Using the gradient images, compute the Harris response for each pixel in the image. The Harris response is calculated as follows:

- R = det(M) - k(trace(M))^2

- where det(M) and trace(M) are the determinant and trace of the matrix M, respectively. The value of k is a constant that depends on the sensitivity of the operator to the corner-like structures. A typical value of k is 0.04.

4. Thresholding: Threshold the Harris response values to obtain a binary image with only the regions of interest. This step is important to remove false positives and retain only the regions that correspond to unique features in the image.

5. Non-maximum suppression: Perform non-maximum suppression to obtain a set of points that represent the unique features in the image. This step involves selecting only the local maxima of the Harris response values and discarding the other points that are not significant.

6. Repeat steps 1 to 5 for all images: Repeat the above steps for all the images in the dataset to extract the unique features in each image.

    
![WhatsApp Image 2023-03-14 at 7 32 04 PM](https://user-images.githubusercontent.com/68791488/225124415-cb2d74a2-0f94-419f-a845-9fae28da55ec.jpeg)

- In summary, the Harris operator and λ can be used to detect and extract unique features in images by computing the Harris response for each pixel in the image and thresholding the response values to obtain a binary image with only the regions of interest. Non-maximum suppression is then performed to obtain a set of points that represent the unique features in the image.

<br/>
<hr/>
<br/>


## SIFT :

Scale-Invariant Feature Transform (SIFT) is a feature detection and extraction algorithm used in computer vision to identify unique features in images that are invariant to scale, rotation, and illumination changes. These features are represented by feature descriptors, which are used to identify and match corresponding features across multiple images.

The SIFT algorithm consists of several steps for generating feature descriptors, which are as follows:

1. Scale-space extrema detection: The first step in the SIFT algorithm is to detect key points in the image that are invariant to scale. This is achieved by computing the difference of Gaussian (DoG) pyramid for the image, which is a series of blurred and downsampled images. The extrema of the DoG pyramid are then detected using the Scale-Space Extrema Detection algorithm.

2. Keypoint localization: The key points detected in the previous step are then refined by eliminating those that have low contrast, are located on edges or corners, or are unstable. This is done by comparing the intensity values at the key point with the values in its local neighborhood.

3. Orientation assignment: Once the key points are detected and localized, their orientations are assigned based on the gradient direction at the key point. This makes the feature descriptors invariant to rotation.




4. Descriptor generation: The final step in the SIFT algorithm is to generate the feature descriptors for each key point. The descriptor is a vector of 128 elements that captures the local image structure around the key point. The descriptor is computed by dividing the local neighborhood around the key point into sub-regions, computing the gradient magnitude and orientation for each sub-region, and then assembling these values into a histogram. The histogram is then normalized to account for changes in illumination and contrast.

5. Descriptor matching: Once the feature descriptors are generated for all the key points in the image, they can be used to match corresponding features across multiple images. This is done by comparing the Euclidean distance between the descriptors of two features. The features with the lowest distance are considered to be a match.

    
![WhatsApp Image 2023-03-14 at 7 31 49 PM](https://user-images.githubusercontent.com/68791488/225124652-f466e75e-ba1e-4baf-b80c-267cbb7f9b0b.jpeg)

- In summary, the SIFT algorithm generates feature descriptors by detecting scale-invariant key points, refining them through keypoint localization, assigning orientation based on gradient direction, and generating a 128-element vector that represents the local image structure around the key point. These feature descriptors are then used to match corresponding features across multiple images.

<br/>
<hr/>
<br/>

## Matching the images:
### SSD : 

Matching image set features is the process of identifying corresponding features between two or more images. One commonly used method for matching features is the Sum of Squared Differences (SSD) technique. The SSD method is based on the principle that corresponding features in two images should have similar intensity values.

The steps involved in matching image set features using SSD are as follows:

1. Compute feature descriptors: The first step in matching image set features using SSD is to compute the feature descriptors for each image. This is typically done using techniques such as SIFT, which generates a vector of numerical values that describe the local image structure around a key point.

2. Select feature pairs: Next, a set of feature pairs is selected for matching. This can be done in various ways, such as selecting the N best matches based on the Euclidean distance between the feature descriptors.

3. Compute the SSD: For each feature pair, the SSD is computed by taking the sum of the squared differences between the corresponding pixel values in the two images. This is calculated using the following formula:

- SSD = Σ(I1(x,y) - I2(x,y))^2

- where I1(x,y) and I2(x,y) are the intensity values of the corresponding pixels in the two images.

4. Select the best match: Once the SSD is computed for all feature pairs, the best match is selected based on the feature pair with the lowest SSD value. This feature pair is considered to be the corresponding pair of features in the two images.

5. Repeat for all feature pairs: The above steps are repeated for all feature pairs, resulting in a set of corresponding features between the two images.


![WhatsApp Image 2023-03-14 at 7 31 33 PM](https://user-images.githubusercontent.com/68791488/225124678-e0e1974f-9313-4564-9afa-fa1932f85650.jpeg)

- In summary, matching image set features using SSD involves computing the feature descriptors for each image, selecting feature pairs, computing the SSD between corresponding pixels in the two images, and selecting the best match based on the lowest SSD value. This process is repeated for all feature pairs, resulting in a set of corresponding features between the two images.

<br/>
<hr/>
<br/>

### NCC : 
Matching image set features using normalized cross-correlation (NCC) is another method for identifying corresponding features between two or more images. This method is based on the principle that corresponding features in two images should have similar patterns, even if their intensity values differ.

The steps involved in matching image set features using NCC are as follows:

1. Compute feature descriptors: The first step in matching image set features using NCC is to compute the feature descriptors for each image. This is typically done using techniques such as SIFT or SURF, which generate a vector of numerical values that describe the local image structure around a key point.

2. Select feature pairs: Next, a set of feature pairs is selected for matching. This can be done in various ways, such as selecting the N best matches based on the Euclidean distance between the feature descriptors.

3. Compute the normalized cross-correlation: For each feature pair, the NCC is computed by calculating the correlation coefficient between the corresponding pixel values in the two images. The correlation coefficient is a measure of how well the patterns in the two images match, even if their intensity values differ. The NCC is calculated using the following formula:



- NCC = Σ((I1(x,y) - μ1) * (I2(x,y) - μ2)) / (σ1 * σ2)

- where I1(x,y) and I2(x,y) are the intensity values of the corresponding pixels in the two images, μ1 and μ2 are the means of the intensities in the corresponding regions, and σ1 and σ2 are the standard deviations of the intensities in the corresponding regions.

4. Select the best match: Once the NCC is computed for all feature pairs, the best match is selected based on the feature pair with the highest NCC value. This feature pair is considered to be the corresponding pair of features in the two images.

5. Repeat for all feature pairs: The above steps are repeated for all feature pairs, resulting in a set of corresponding features between the two images.

    
![WhatsApp Image 2023-03-14 at 7 59 27 PM](https://user-images.githubusercontent.com/68791488/225125058-17cb0214-6759-44b2-8d35-4aa922aab3c1.jpeg)

- In summary, matching image set features using NCC involves computing the feature descriptors for each image, selecting feature pairs, computing the NCC between corresponding pixels in the two images, and selecting the best match based on the highest NCC value. This process is repeated for all feature pairs, resulting in a set of corresponding features between the two images.

<br/>
<hr/>
<br/>

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a new branch: `git checkout -b feature/new-feature`
3. Make changes and commit them: `git commit -m "Add new feature"`
4. Push the changes to the branch: `git push origin feature/new-feature`
5. Submit a pull request

<br/>
<hr/>
<br/>
## Developers

<table align="center">
  <tr>
    <td align="center"><a href="https://github.com/AhmedRaouf481"><img src="https://avatars.githubusercontent.com/u/62951712?v=4" width="100px;" alt=""/><br /><sub><b>Ahmed Abdelraouf</b></sub></a></td>
    <td align="center"><a href="https://github.com/Zeyad-Amr"><img src="https://avatars.githubusercontent.com/u/68791488?v=4" width="100px;" alt=""/><br /><sub><b>Zeyad Amr</b></sub></a></td>
    <td align="center"><a href="https://github.com/momen882001"><img src="https://avatars.githubusercontent.com/u/84360276?v=4" width="100px;" alt=""/><br /><sub><b>Mo'men Mohamed</b></sub></a></td>
    <td align="center"><a href="https://github.com/michaelhany510"><img src="https://avatars.githubusercontent.com/u/69060386?v=4" width="100px;" alt=""/><br /><sub><b>Micheal Hany</b></sub></a></td>
    <td align="center"><a href="https://github.com/Mazen-Aboulkhair"><img src="https://avatars.githubusercontent.com/u/84642500?v=4" width="100px;" alt=""/><br /><sub><b>Mazen Tarek</b></sub></a></td>
  </tr>
</table>

