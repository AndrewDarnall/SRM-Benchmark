/**
 * Implementation source file for the Statistical Region Merging Algorithm
 */
#include <cmath>
#include "../include/libsrm_cpp/srm.hpp"

#include <opencv2/opencv.hpp>


/**
 * SRM: The constructor for the Algorithm Object
 * @param _Q: by default Q = 32, and it guides / dictates
 *            the granularity of the segmentation
 * @param _img_size: the size of the image (width * height)
 * @param _max_regions: The maximum ammount of regions chosen
 *                      for a given picture (to prevent overmerging)
 * @param _min_size: parameter chosen to avoid undermerging
 */
SRM::SRM(int _Q, int _max_regions, float _min_size) {
    this->Q = _Q;
    this->g = 256;
    this->imgSize = 0;
    this->maxRegions = _max_regions;
    this->minSize = _min_size;
    this->delta = std::log(6) + 2 * std::log(this->imgSize);
}


/**
 * run:
 * @param path: Path to the Image
 */
void SRM::run(cv::Mat& img) {

    this->imgSize = img.rows * img.cols;
    this->minSize = this->minSize * static_cast<float>(this->imgSize);
    
    cv::Mat floatImage;
    img.convertTo(floatImage, CV_32F);


    std::vector<int> rank(this->imgSize, 1);
    std::vector<int> parent;
    for (int i = 0; i < this->imgSize; i++) {
        parent.push_back(i);
    }

    if (this->maxRegions < 0) {
        this->maxRegions = this->imgSize;
    }

    // End of initialization block

    std::vector<std::pair<int, int>> edgeList = this->makeEdgePairList(floatImage, static_cast<int>(img.rows), static_cast<int>(img.cols));

    for (const auto& pair : edgeList) {
        std::cout << "(" << pair.first << "," << pair.second << ")\t" << std::endl;
    }
}


/**
 * makeEdgePairList: 
 * 
 */
std::vector<std::pair<int, int>>& SRM::makeEdgePairList(const cv::Mat& img, int rows, int cols) {

    std::vector<std::pair<int, int>>* edgeList = new std::vector<std::pair<int, int>>;

    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            index = i * rows + j;
            if (i != rows - 1) {
                edgeList->push_back(std::make_pair(index, index + cols));
            }
            if (j != cols - 1) {
                edgeList->push_back(std::make_pair(index, index + 1));
            }
        }
    }

    this->sortEdgePairs(img, *edgeList);

    return *edgeList;
}


/**
 * sortEdgePairs: 
 * 
 */
void SRM::sortEdgePairs(const cv::Mat& image, std::vector<std::pair<int,int>>& edgeList) {
        
        //// ---- TO TEST


        // Define the sorting function using a lambda expression
        auto diff = [this, &image](const std::pair<int, int>& p) {
            int r1 = p.first;
            int r2 = p.second;

            // Calculate the maximum absolute difference between the rows r1 and r2
            cv::Mat diffMat;
            cv::absdiff(image.row(r1), image.row(r2), diffMat);  // Compute absolute difference

            // Find the maximum difference in the resulting difference matrix
            return *std::max_element(diffMat.begin<uchar>(), diffMat.end<uchar>());
        };

        // Actually sort the Array using the lambda expression as the comparator
        std::sort(edgeList.begin(), edgeList.end(),
            [&diff](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                return diff(a) < diff(b);
            });


        /////// ---- TO TEST
}

/**
 * evaluatePredicate: The P(.) function from the paper
 * @param parentA: The region of interest
 */
bool SRM::evaluatePredicate(int parentA) {
    return false;
}

/**
 * merge: Performs the actual merging of the regions
 * @param parentA: Region 1
 * @param parentB: Region 2
 * 
 */
void SRM::merge(int parentA, int parentB) {

}


/**
 * getParent: Obtains the root element in the UnionFind
 * @param parentA: Query region
 * 
 */
int SRM::getParent(int parentA) {
    return 0;
}

/**
 * mergeOcclusions:
 * 
 */
void SRM::mergeOcclusions() {

}

/**
 * mergeSmallerRegions: 
 */
void SRM::mergeSmallerRegions() {

}


/**
 * retrieveMaxParents:
 * 
 */
std::vector<int>& SRM::retrieveMaxParents() {
    std::vector<int>* vec = new std::vector<int>;
    return *vec;
}