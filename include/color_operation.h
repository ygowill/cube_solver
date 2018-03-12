#ifndef CUBE_SOLVER_COLOR_OPERATION_H
#define CUBE_SOLVER_COLOR_OPERATION_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/core.hpp>
#include "cube_data.h"

void cube_color_reduce(cv::Mat& src, cv::Mat& dst);
void my_kmeans(cv::Mat& src,cv::Mat& dst,int clusterCount,int attempts);
void get_cube_color(cv::Mat& roi,std::array<char, BLOCKSIZE> color);
char get_block_color(cv::Mat& roi);

#endif //CUBE_SOLVER_COLOR_OPERATION_H