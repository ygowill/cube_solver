#ifndef CUBE_SOLVER_CUBE_BOUND_H
#define CUBE_SOLVER_CUBE_BOUND_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "cube_data.h"
#include "cube_block.h"

void number_signal(cv::Point2f src,cv::Point2f dst,int sig[]);
void findBound(std::vector<std::array<cv::Point2f,CUBESHAPE> >& corners,std::array<cv::Point2f,CUBESHAPE>& bounds,int mode);

#endif //CUBE_SOLVER_CUBE_BOUND_H


