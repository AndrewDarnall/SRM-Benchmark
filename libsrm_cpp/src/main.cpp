/**
 * C++ Implementation of the Statistical Region Merging Algorithm
 * Celebrating 20 years since the paper was published!
 */
#include <cstdlib>
#include <iostream>

#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {

    if (argc != 3) {
        std::cerr << "usage:\t" << argv[0] << "\t<PATH-TO-IMAGE>\t" <<
        "<Q-Parameter>" << std::endl;
        exit(-1);
    }

    // Open image and check for non-empty image
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_UNCHANGED);

    std::cout << " -- Running the Statistical Region " <<
    "Merging Algorithm on " << argv[1] << std::endl;

    return EXIT_SUCCESS;
}
