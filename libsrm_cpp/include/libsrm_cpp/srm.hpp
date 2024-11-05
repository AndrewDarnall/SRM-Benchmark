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
        float delta;
        int imgSize;
        int minSize;
        int maxRegions;

    public:
        SRM(int, int, int);

        void run(cv::Mat);
        std::vector<std::pair<int, int>>& makeEdgePairList(int, int);
        std::vector<std::pair<int, int>>& sortEdgePairs(std::vector<std::pair<int, int>>&);
        bool evaluatePredicate(int);
        void merge(int, int);
        int getParent(int);
        void mergeOcclusions();
        void mergeSmallerRegions();
        std::vector<int> retrieveMaxParents();


};

#endif