/**
 * C++ Implementation of the Statistical Region Merging Algorithm
 * Celebrating 20 years since the paper was published!
 */
#include <cstdlib>
#include <iostream>

#include <opencv2/opencv.hpp>

#include "srm.cpp"

int main(int argc, char** argv) {

    if (argc != 5) {
        std::cerr << "usage:\t" << argv[0] << "\t<PATH-TO-IMAGE>\t" <<
        "<Q-Parameter--Default=32>\t<Max-Regions--Default=15>\t" << 
        "<Min-Size--Default=0.001>" << std::endl;
        return EXIT_FAILURE;
    }

    cv::Mat img = cv::imread(argv[1]);

    if (img.empty()) {
        std::cerr << " !! Error Opening the Image !! " << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << " -- Running the Statistical Region " <<
    "Merging Algorithm on " << argv[1] << std::endl;

    // Algorithm methods ...
    SRM* srm = new SRM(atoi(argv[2]), atoi(argv[3]), atof(argv[4]));
    srm->run(img);
    

    std::cout << " == Finished Running the" << 
    " SRM Algorithm == " << std::endl;

    return EXIT_SUCCESS;
}
