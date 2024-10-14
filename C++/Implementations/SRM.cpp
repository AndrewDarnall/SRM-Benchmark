#include "SRM.hpp"
#include <algorithm>


int SRM::regionCount = 0;

void SRM::createTupleArray(const cv::Mat& image, std::vector<PixelTuple>& tupVec)
{
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i,j);

            PixelTuple tup = std::make_tuple(static_cast<int>(pixel[2]), static_cast<int>(pixel[1]), static_cast<int>(pixel[0]));
            tupVec.push_back(tup);
        }
    }
}

void SRM::createCouplePixelTable(const std::vector<PixelTuple>& data, int w, int h, std::vector<Region*>& regions, std::vector<RegionCouple*>& table)
{
    // Initialize Region objects and store pointers
    regions.resize(data.size());
    for (size_t c = 0; c < regions.size(); ++c) {
        regions[c] = new Region(data[c], static_cast<int>(c));  // Create Region dynamically
        std::cout << " - Region:\t(" << regions[c]->getPixelChannel(0) << "," << regions[c]->getPixelChannel(1);
        std::cout << "," << regions[c]->getPixelChannel(2) << ")" << std::endl;
    }

    int counter = 0;

    // Horizontal neighbors
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w - 1; ++x) {
            int c = y * w + x;
            int cc = y * w + x + 1;
            table.push_back(new RegionCouple(regions[c], regions[cc]));  // Create RegionCouple dynamically
            std::cout << " - RegionCouple:\t(" << table.back()->region1->getPixelChannel(0);
            std::cout << "," << table.back()->region1->getPixelChannel(1) << "," << table.back()->region1->getPixelChannel(0) << "," << table.back()->region2->getPixelChannel(0) << ")" << std::endl;
            ++counter;
        }
    }

    // Vertical neighbors
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h - 1; ++y) {
            int c = y * w + x;
            int cc = (y + 1) * w + x;
            table.push_back(new RegionCouple(regions[c], regions[cc]));  // Create RegionCouple dynamically
            std::cout << " - RegionCouple:\t(" << table.back()->region1->getPixelChannel(0) << "," << table.back()->region2->getPixelChannel(0) << ")" << std::endl;
            ++counter;
        }
    }

    std::sort(table.begin(), table.end());

}

int SRM::getRegionCount()
{
    return regionCount;
}

bool SRM::mergingPredicate(Region* region1, Region* region2, int num1, int num2, double b, int twoQ)
{
        // Calculate a1 and a2 based on the formula
    double a1 = 256 / std::sqrt(twoQ * region1->getCardinality());
    double a2 = 256 / std::sqrt(twoQ * region2->getCardinality());

    // Calculate bR1 and bR2
    double bR1 = a1 * std::sqrt(std::log(num1) - b);
    double bR2 = a2 * std::sqrt(std::log(num2) - b);

    // Calculate R, G, B medians for both regions
    int R1med = region1->getChannelSum(0) / region1->getCardinality();
    int G1med = region1->getChannelSum(1) / region1->getCardinality();
    int B1med = region1->getChannelSum(2) / region1->getCardinality();

    int R2med = region2->getChannelSum(0) / region2->getCardinality();
    int G2med = region2->getChannelSum(1) / region2->getCardinality();
    int B2med = region2->getChannelSum(2) / region2->getCardinality();

    // Calculate threshold
    double th = std::sqrt(bR1 * bR1 + bR2 * bR2);

    // Return true if differences in R, G, B are within the threshold
    return std::abs(R2med - R1med) <= th
        && std::abs(G2med - G1med) <= th
        && std::abs(B2med - B1med) <= th;
}

std::vector<PixelTuple> SRM::evaluate(const cv::Mat& image, int Q)
{
    int w = image.cols;
    int h = image.rows;
    std::vector<PixelTuple> data(w * h);
    // cv::Mat(image).reshape(0, h).copyTo(data);
    // cv::Mat(image).reshape(0, h);

    createTupleArray(image, data);

    std::vector<Region*> region(w * h);
    std::vector<RegionCouple*> table((w - 1) * h + w * (h - 1));
    createCouplePixelTable(data, w, h, region, table);
    
    std::vector<int> numRegionWithKPixel(w * h - 1);
    numRegionWithKPixel[0] = w * h;

    double b = (std::log(1) - (std::log(6) + 2 * std::log(w * h)));
    int twoQ = 2 * Q;

    int regionCount = w * h;

    std::cout << " table.at(0):\t" << table.at(0) << std::endl;

    for (size_t i = 0; i < table.size(); ++i) {
        Region* region1 = table[i]->region1->findCompress(table[i]->region1);
        Region* region2 = table[i]->region2->findCompress(table[i]->region2);

        if (region1 != region2) {
            int num1 = numRegionWithKPixel[region1->getCardinality() - 1];
            int num2 = numRegionWithKPixel[region2->getCardinality() - 1];

            if (mergingPredicate(region1, region2, num1, num2, b, twoQ)) {
                numRegionWithKPixel[region1->getCardinality() - 1]--;
                numRegionWithKPixel[region2->getCardinality() - 1]--;
                numRegionWithKPixel[region1->getCardinality() + region2->getCardinality() - 1]++;

                region2->merge(region1);
                regionCount--;
            }
        }
    }

    std::vector<PixelTuple> res(w * h);

    for (size_t i = 0; i < region.size(); ++i) {
        if (!region[i]->isDone()) {
            region[i]->setDone(true);
            Region* r;
            r = r->findCompress(region[i]);

            // To pudate since I am using color tuples
            int red_sum = r->getChannelSum(0);
            int green_sum = r->getChannelSum(1);
            int blue_sum = r->getChannelSum(2);

            red_sum = red_sum / r->getCardinality();
            green_sum = green_sum / r->getCardinality();
            blue_sum = blue_sum / r->getCardinality();

            r = region[i];

            while (r) {
                res[r->getPosition()] = std::make_tuple(red_sum, green_sum, blue_sum);
                r->setDone(true);
                r = r->getParent();
            }
        }
    }

    return res;
}