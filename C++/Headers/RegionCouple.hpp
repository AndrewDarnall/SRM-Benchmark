#ifndef REGIONCOUPLE_HPP
#define REGIONCOUPLE_HPP

#include "Region.hpp"
#include <ostream>

class RegionCouple {

    private:

        int intensity_distance;

    public:

        Region* region1;
        Region* region2;

        RegionCouple(Region* region_1, Region* region_2);
        
        bool compareByIntensityDiff(const RegionCouple& target_region);
        int getIntensityDistance() const;
        Region* getRegion(int); 

        bool operator < (const RegionCouple&) const;
        friend std::ostream& operator<<(std::ostream& os, const RegionCouple& couple);

};


#endif