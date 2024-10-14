#ifndef REGION_HPP
#define REGION_HPP

#include <tuple>

typedef std::tuple<int, int, int> PixelTuple;

class Region {

    private:

        int sum_red, sum_green, sum_blue;
        int cardinality;
        int position;
        int red, green, blue;
        // Change to a pointer to fix the type-declaration error
        Region* parent;
        bool done;


    public:

        Region(const PixelTuple& color, int positon);
        Region() = default;

        void merge(Region* region);
        bool isTop();
        Region* findCompress(Region* region);
        int getPixelChannel(int channel_no) const;
        int getChannelSum(int channel_no) const;
        int getCardinality();
        int getPosition() const;
        Region* getParent() const;
        bool isDone() const;
        void setDone(bool);


};

#endif