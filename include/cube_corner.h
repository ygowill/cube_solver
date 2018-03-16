#ifndef CUBE_SOLVER_CUBE_CORNER_H
#define CUBE_SOLVER_CUBE_CORNER_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "cube_data.h"

void findFrontCorner(std::vector<std::vector<cv::Point> >& squares, std::vector<std::array<cv::Point2f,4> >& corners);
void findRightCorner(std::vector<std::vector<cv::Point> >& squares, std::vector<std::array<cv::Point2f,4> >& corners);
void findDownCorner(std::vector<std::vector<cv::Point> >& squares, std::vector<std::array<cv::Point2f,4> >& corners);

#endif //CUBE_SOLVER_CUBE_CORNER_H