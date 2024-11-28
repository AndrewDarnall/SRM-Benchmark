/**
 * Utility functions for the Algorithm
 */
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <utility>

#include <opencv2/opencv.hpp>

class DiffComparator {
private:
  const cv::Mat &image;

public:
  DiffComparator(const cv::Mat &);

  int operator()(const std::pair<int, int> &) const;
};

const std::string getBaseName(const std::string &);

#endif
