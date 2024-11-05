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
SRM::SRM(int _Q, int _max_regions, int _min_size) {
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
void SRM::run(cv::Mat img) {

    this->imgSize = img.rows * img.cols;
    this->minSize = this->minSize * this->imgSize;
    
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

    std::vector<int> edgeList = this->makeEdgePairList(img.rows, img.cols);


}


/**
 * makeEdgePairList: 
 * 
 */
std::vector<std::pair<int, int>>& SRM::makeEdgePairList(int rows, int cols) {

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

    return this->sortEdgePairs(edgeList);
}


/**
 * sortEdgePairs: 
 * 
 */
std::vector<std::pair<int, int>>& SRM::sortEdgePairs(std::vector<std::pair<int,int>>& edgeList) {
    
}

/**
 * evaluatePredicate: The P(.) function from the paper
 * @param parentA: The region of interest
 */
bool SRM::evaluatePredicate(int parentA) {

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

}

/**
 * mergeOcclusions:
 * 
 */
void SRM::mergeOcclusions() {

}


/**
 * retrieveMaxParents:
 * 
 */
std::vector<int> SRM::retrieveMaxParents() {

}