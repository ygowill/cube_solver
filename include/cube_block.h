#ifndef CUBE_SOLVER_CUBE_BLOCK_H
#define CUBE_SOLVER_CUBE_BLOCK_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "cube_data.h"

void findFrontKeyBlock(std::vector<std::array<cv::Point2f,4> >& corners,int &core_square_index);
void findRightKeyBlock(std::vector<std::array<cv::Point2f,4> >& corners,int &core_square_index);
void findDownKeyBlock(std::vector<std::array<cv::Point2f,4> >& corners,int &core_square_index);

#endif //CUBE_SOLVER_CUBE_BLOCK_H