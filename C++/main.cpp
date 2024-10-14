/**
 * ------------------------------------------------------------------------------------------------------------
 *  The C++ Implementation of the Statistical Region Merging - A Region Growing Image Segmentation Algorithm
 * 
 *  Author: Andrew R. Darnall (TheComputerScientist)
 *  
 *  Source: https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=1335450
 * ------------------------------------------------------------------------------------------------------------
 * 
 * */

#include <iostream>
#include <cstdlib>
#include "SRM.hpp"
#include "UtilityFunctions.hpp"
#include <opencv2/opencv.hpp>


int main(int argc, char** argv)
{


    // Check the path of the input image
    if (argc != 3) {
        std::cerr << "usage:'\t<" << argv[0] << "\t<path-to-input-image>\t<Q>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string fileName = argv[1];
    std::string outputPath = createOutputPath(fileName);

    cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << " !! Error Opening the image:\t" << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << " -- Running the SRM Algorithm -- " << std::endl;

    SRM* srm = new SRM();
    std::vector<PixelTuple> pixelTuple = srm->evaluate(image, atoi(argv[2]));
    saveImage(pixelTuple, image, outputPath);

    std::cout << " ++ Finished Running the SRM Algorithm ++ " << std::endl; 


    return EXIT_SUCCESS;
}