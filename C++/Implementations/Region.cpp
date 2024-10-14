#include "Region.hpp"
#include <iostream>

Region::Region(const PixelTuple& pixel, int position) : parent(nullptr)
{

    this->red = std::get<0>(pixel);
    this->green = std::get<1>(pixel);
    this->blue = std::get<2>(pixel);

    this->position = position;
    this->sum_red = std::get<0>(pixel);
    this->sum_green = std::get<1>(pixel);
    this->sum_blue = std::get<2>(pixel);
    this->cardinality = 1;
}

void Region::merge(Region* region)
{
    this->sum_red += region->sum_red;
    this->sum_green += region->sum_green;
    this->sum_blue += region->sum_blue;
    region->parent = this;
}

bool Region::isTop()
{
    return parent == nullptr;
}

Region* Region::findCompress(Region* region)
{
    if (region->isTop()) {
        return region;
    } else {
        region->parent = findCompress(region->parent);
        return region->parent;
    }
}


int Region::getPixelChannel(int channel_no) const
{
    switch(channel_no) {
        case 0: {
            return this->red;
            break;
        }
        case 1: {
            return this->green;
            break;
        }
        case 2: {
            return this->blue;
            break;
        }
        default: {
            std::cout << " --- Error case --- " << std::endl;
            return -1;
        }
    }
}

int Region::getChannelSum(int channel_no) const
{
    switch(channel_no) {
        case 0: {
            return this->sum_red;
            break;
        }
        case 1: {
            return this->sum_green;
            break;
        }
        case 2: {
            return this->sum_blue;
            break;
        }
        default: {
            std::cout << " --- Error case --- " << std::endl;
            return -1;
        }
    }
}

int Region::getCardinality()
{
    return this->cardinality;
}

int Region::getPosition() const
{
    return this->position;
}

Region* Region::getParent() const 
{
    return this->parent;
}

bool Region::isDone() const
{
    return this->done;
}

void Region::setDone(bool var)
{
    this->done = var;
}