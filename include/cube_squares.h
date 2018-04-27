#ifndef CUBE_SOLVER_CUBE_SQUARES_H
#define CUBE_SOLVER_CUBE_SQUARES_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "cube_data.h"

bool checkExist(std::vector<cv::Point>& square, std::vector<std::vector<cv::Point> >& exist_squares,int maxRange);
void findSquares( const cv::Mat& image, Cube& cube);
void drawSquares( cv::Mat& image, const std::vector<std::vector<cv::Point> >& squares);

#endif //CUBE_SOLVER_CUBE_SQUARES_H