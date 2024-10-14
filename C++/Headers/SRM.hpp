#ifndef SRM_HPP
#define SRM_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include "Region.hpp"
#include "RegionCouple.hpp"

class SRM 
{
    private:
        static int regionCount;
    public:
        static void createTupleArray(const cv::Mat&, std::vector<PixelTuple>&);
        static int getRegionCount();
        static void createCouplePixelTable(const std::vector<PixelTuple>&, int, int, std::vector<Region*>&, std::vector<RegionCouple*>&);
        static bool mergingPredicate(Region*, Region*, int, int, double, int);
        static std::vector<PixelTuple> evaluate(const cv::Mat&, int);

};

#endif