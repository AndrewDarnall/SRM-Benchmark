#ifndef UTILITYFUNCTION_HPP
#define UTILITYFUNCTIONS_HPP

#include <opencv2/opencv.hpp>
#include <string>

#include "srmtypes.hpp"

void saveImage(const std::vector<PixelTuple>&, const cv::Mat&, const std::string&);

std::string getFileExtension(const std::string&);
std::string getBaseName(const std::string&);
std::string createOutputPath(const std::string&);

#endif