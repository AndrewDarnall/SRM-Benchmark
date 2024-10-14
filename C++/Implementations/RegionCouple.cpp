#include "RegionCouple.hpp"
#include <cmath>


RegionCouple::RegionCouple(Region* region_1, Region* region_2) : region1(region_1), region2(region_2)
{
    int red_1 = region_1->getPixelChannel(0);
    int green_1 = region_1->getPixelChannel(1);
    int blue_1 = region_1->getPixelChannel(2);

    int red_2 = region_2->getPixelChannel(0);
    int green_2 = region_2->getPixelChannel(1);
    int blue_2 = region_2->getPixelChannel(2);

    int red_diff = std::abs(red_1 - red_2);
    int green_diff = std::abs(green_1 - green_2);
    int blue_diff = std::abs(blue_1 - blue_2);

    this->intensity_distance = std::max(std::max(red_diff, green_diff), blue_diff);
}

int RegionCouple::getIntensityDistance() const
{
    return this->intensity_distance;
}

bool RegionCouple::compareByIntensityDiff(const RegionCouple& target_region)
{
    return this->intensity_distance < target_region.getIntensityDistance();
}


bool RegionCouple::operator<(const RegionCouple& other) const
{
    return (region1->getPosition() < other.region2->getPosition());
}

std::ostream& operator<<(std::ostream& os, const RegionCouple& couple) 
{
    os << "RegionCouple:" << std::endl;
    
    if (couple.region1 != nullptr) {
        os << "  Region 1 - R: " << couple.region1->getPixelChannel(0)
           << ", G: " << couple.region1->getPixelChannel(1)
           << ", B: " << couple.region1->getPixelChannel(2)
           << std::endl;
    }
    
    if (couple.region2 != nullptr) {
        os << "  Region 2 - R: " << couple.region2->getPixelChannel(0)
           << ", G: " << couple.region2->getPixelChannel(1)
           << ", B: " << couple.region2->getPixelChannel(2)
           << std::endl;
    }
    
    return os;
}