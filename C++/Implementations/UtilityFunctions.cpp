#include "UtilityFunctions.hpp"

void saveImage(const std::vector<PixelTuple>& resultVec, const cv::Mat& image, const std::string& outputPath)
{
    int counter = 0;
    int height = image.rows;
    int width = image.cols;

    cv::Mat output_image(height, width, CV_8UC3);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cv::Vec3b color;
            PixelTuple tup = resultVec[counter];
            color[0] = static_cast<uchar>(std::get<2>(tup));
            color[1] = static_cast<uchar>(std::get<1>(tup));
            color[2] = static_cast<uchar>(std::get<0>(tup));
            output_image.at<cv::Vec3b>(i, j) = color;
            counter += 1;
        }
    }

    cv::imwrite(outputPath, output_image);

}

std::string getFileExtension(const std::string& fileName) 
{
    size_t dotPos = fileName.find_last_of('.');
    if (dotPos != std::string::npos && dotPos != 0) {
        return fileName.substr(dotPos + 1);
    }
    return ""; 
}


std::string getBaseName(const std::string& fileName) 
{

    size_t slashPos = fileName.find_last_of("/\\");
    std::string base = (slashPos == std::string::npos) ? fileName : fileName.substr(slashPos + 1);


    size_t dotPos = base.find_last_of('.');
    if (dotPos != std::string::npos) {
        base = base.substr(0, dotPos);
    }

    return base;
}

std::string createOutputPath(const std::string& fileName)
{
    std::string baseName = getBaseName(fileName);
    std::string extension = getFileExtension(fileName);
    std::string outputPath = "./Program-Out/" + baseName + "_segmented." + extension;
    return outputPath;
}