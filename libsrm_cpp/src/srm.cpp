/**
 * Implementation source file for the Statistical Region Merging Algorithm
 */
#include <cmath>
#include <string>
#include <sstream>
#include <map>

#include "../include/libsrm_cpp/srm.hpp"
#include "../include/libsrm_cpp/utils.hpp"

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
SRM::SRM(int _Q, int _max_regions, double _min_size, cv::Mat& image) : img(image) {
    this->imgRows = this->img.rows;
    this->imgCols = this->img.cols;
    this->Q = _Q;
    this->g = 256;
    this->imgSize = this->imgRows * this->imgCols;
    this->maxRegions = _max_regions;
    this->minSize = _min_size * static_cast<float>(this->imgSize);
    this->delta = std::log(6.0) + 2.0 * std::log(static_cast<double>(this->imgSize));

    this->rank = std::vector<int>(this->imgSize, 1);

    for (int i = 0; i < this->imgSize; i++) {
        this->parent.push_back(i);
    }

    if (this->maxRegions < 0) {
        this->maxRegions = this->imgSize;
    }
}


/**
 * run:
 * @param path: Path to the Image
 */
void SRM::run() {
    
    cv::Mat floatImage;
    this->img.convertTo(floatImage, CV_32F);
    this->img = floatImage.reshape(1, this->getImageSize());


    // 1) Sort the list of pairs (4-Connected Neighbors)
    std::vector<std::pair<int, int>> edgeList = this->makeEdgePairList(this->getImageRows(), this->getImageCols());


    // 2) Iterate through the list of pairs and perform the statistical test
    for (const std::pair<int, int>& p : edgeList) {
        
        int parentA = this->getParent(p.first);
        int parentB = this->getParent(p.second);

        if ((parentA != parentB) && (this->predicate(parentA, parentB))) {
            this->merge(parentA, parentB);
        } 

    }

    // // 3) Check for occluded regions
    // if (this->maxRegions > 0) {
    //     this->mergeOcclusions();
    // }

    // // 4) Check for smaller regions
    // if (this->minSize > 0) {
    //     this->mergeSmallerRegions();
    // }

    // 5) Change the color of the image accordingly (actual segmentation)
    for (int i = 0; i < this->imgSize; i++) {
        cv::Vec3f color = this->img.at<cv::Vec3f>(0, this->getParent(i));
        this->img.at<cv::Vec3f>(0, i) = color;
    }

    // 6) Reshape the image and save it to the object's state
    this->img = this->img.reshape(3, this->getImageRows());
    this->img.convertTo(this->img, CV_8U);

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

    this->sortEdgePairs(*edgeList);

    return *edgeList;
}


/**
 * sortEdgePairs: 
 * 
 */
void SRM::sortEdgePairs(std::vector<std::pair<int,int>>& edgeList) {
    
        DiffComparator diffComparator(this->img);

        std::stable_sort(edgeList.begin(), edgeList.end(),
            [&diffComparator](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                return diffComparator(a) < diffComparator(b);
            });

}


/**
 * evaluatePredicate: The P(.) function from the paper
 * @param parentA: The first region of interest
 * @param parentB: The second region of interest
 */
bool SRM::predicate(int parentA, int parentB) {

    double predicateA = this->evaluatePredicate(parentA);
    double predicateB = this->evaluatePredicate(parentB);
    cv::Vec3f comparrison = (this->img.at<cv::Vec3f>(0, parentA) - this->img.at<cv::Vec3f>(0, parentB));
    comparrison = comparrison.mul(comparrison);
    
    auto checkPredicate = [](const cv::Vec3f& squaredDiff, double threshold) {
        return (squaredDiff[0] < threshold) && (squaredDiff[1] < threshold) && (squaredDiff[2] < threshold);
    };

    return (checkPredicate(comparrison, (predicateA + predicateB)));
}

/**
 * predicate: Computes the actual predicate
 *            on a single region
 */
double SRM::evaluatePredicate(int parentA) {

    return (
        (std::pow(this->g, 2) / static_cast<double>(2 * this->Q * this->rank[parentA])) *
        static_cast<double>(std::min(this->g, this->rank[parentA])) *
        std::log(static_cast<double>(this->rank[parentA]) + 1) +
        this->delta
    );
}

/**
 * merge: Performs the actual merging of the regions
 * @param parentA: Region 1
 * @param parentB: Region 2
 * 
 */
void SRM::merge(int parentA, int parentB) {
    int sum1 = this->rank[parentA];
    int sum2 = this->rank[parentB];
    
    cv::Vec3f color = (
        (this->img.at<cv::Vec3f>(0, parentA) * sum1) + 
        (this->img.at<cv::Vec3f>(0, parentB) * sum2)
    ) / 
    (static_cast<float>(sum1) + static_cast<float>(sum2));

    if (sum1 < sum2) {
        int swap = parentA;
        parentA = parentB;
        parentB = parentA;
    }

    this->parent[parentB] = parentA;
    this->rank[parentA] += this->rank[parentB];
    this->img.at<cv::Vec3f>(0, parentA) = color;
}


/**
 * getParent: Obtains the root element in the UnionFind
 * @param parentA: Query region
 * 
 */
int SRM::getParent(int parentA) {
    if (this->parent[parentA] == parentA) {
        return parentA;
    }
    // Lazy propagation
    int p = this->getParent(this->parent[parentA]);
    return p;
}

/**
 * mergeOcclusions:
 * 
 */
void SRM::mergeOcclusions() {
    for (int i = 1; i < this->getImageSize(); i++) {
        int r1 = this->getParent(i);
        int r2 = this->getParent(i - 1);
        if ((r1 != r2) && (this->rank[r1] <= this->minSize)) {
            this->merge(r1, r2);
        }
    }
}

/**
 * mergeSmallerRegions: 
 */
void SRM::mergeSmallerRegions() {
    
    std::vector<int> maxParents = this->retrieveMaxParents();
    if (maxParents.size() > this->maxRegions) {
        std::vector<int> allowedParents(maxParents.begin(), maxParents.begin() + this->maxRegions);
        for (int i = 0; i < this->getImageSize(); i++) {
            int r1 = this->getParent(i);
            int r2 = this->getParent(i - 1);
            if ((r1 != r2) && (std::find(allowedParents.begin(), allowedParents.end(), r1) == allowedParents.end())) {
                this->merge(r1, r2);
            }
        }
    }

}


/**
 * retrieveMaxParents:
 * 
 */
std::vector<int>& SRM::retrieveMaxParents() {

    std::vector<int>* sortedKeys = new std::vector<int>;
    std::map<int, int> parentsCounts;

    for (int pt : this->parent) {
        parentsCounts[pt]++;
    }

    std::vector<std::pair<int, int>> countsVector(parentsCounts.begin(), parentsCounts.end());

    std::sort(countsVector.begin(), countsVector.end(),
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second;
              });

    for (const auto& pair : countsVector) {
        sortedKeys->push_back(pair.first);
    }

    return *sortedKeys;
}

/**
 * Saves the segmented image
 */
void SRM::saveImage(const std::string& asbPath) {

    std::ostringstream oss;
    oss << "Segmented_" << getBaseName(asbPath);
    std::string fileName = oss.str();

    cv::imwrite(fileName, this->img);

}

int SRM::getImageRows() const {
    return this->imgRows;
}

int SRM::getImageCols() const {
    return this->imgCols;
}

int SRM::getImageSize() const {
    return this->imgSize;
}