/**
 * Header for the definition of the SRM Algorithm, designed and implemented in OOP-Style
 */
#ifndef SRM_HPP
#define SRM_HPP

#include <string>
#include <vector>
#include <utility>

#include <opencv2/opencv.hpp>

class SRM {

    private:
        
        int Q;
        int g;
        double delta;
        int imgSize;
        double minSize;
        int maxRegions;
        int imgRows;
        int imgCols;
        std::vector<int> rank;
        std::vector<int> parent;
        cv::Mat& img;

    public:
        SRM(int, int, double, cv::Mat&);

        void run();
        std::vector<std::pair<int, int>>& makeEdgePairList(int, int);
        void sortEdgePairs(std::vector<std::pair<int, int>>&);
        double evaluatePredicate(int);
        bool predicate(int, int);
        void merge(int, int);
        int getParent(int);
        void mergeOcclusions();
        void mergeSmallerRegions();
        std::vector<int>& retrieveMaxParents();
        void saveImage(const std::string&);

        int getImageRows() const;
        int getImageCols() const;
        int getImageSize() const;


};

#endif