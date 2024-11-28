#include <filesystem>

#include "../include/libsrm_cpp/utils.hpp"

DiffComparator::DiffComparator(const cv::Mat &image) : image(image) {}

int DiffComparator::operator()(const std::pair<int, int> &p) const {

  int r1 = p.first;
  int r2 = p.second;

  cv::Mat diffMat;
  cv::absdiff(image.row(r1), image.row(r2), diffMat);

  return static_cast<int>(
      *std::max_element(diffMat.begin<double>(), diffMat.end<double>()));
}

const std::string getBaseName(const std::string &filePath) {
  return std::filesystem::path(filePath).filename();
}
