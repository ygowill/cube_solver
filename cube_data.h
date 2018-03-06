#pragma once

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
const int MAXRANGE = 1000;
const int MAXTAN = 3;
const int PICSIZE = 200;
const int CUBESHAPE = 4;
const int FRAMESIZE_X = 1280;
const int FRAMESIZE_Y = 720;
const int BLOCKSIZE = CUBESHAPE*CUBESHAPE;
const int FRONT_DISTANCE_COMPENSATION_X = 6;
const int FRONT_DISTANCE_COMPENSATION_Y = 5;
const int FRONT_DISTANCE_COMPENSATION_XY_X = 30;
const int FRONT_DISTANCE_COMPENSATION_XY_Y = 0;
const int RIGHT_DISTANCE_COMPENSATION_X = 4;
const int RIGHT_DISTANCE_COMPENSATION_Y = 6;
const int RIGHT_DISTANCE_COMPENSATION_XY_X = -35;
const int RIGHT_DISTANCE_COMPENSATION_XY_Y = 20;
const int DOWN_DISTANCE_COMPENSATION_X = 4;
const int DOWN_DISTANCE_COMPENSATION_Y = 5;
const int DOWN_DISTANCE_COMPENSATION_XY_X = 5;
const int DOWN_DISTANCE_COMPENSATION_XY_Y = -25;

extern std::vector<std::vector<cv::Point> > front_squares;
extern std::array<cv::Point2f,CUBESHAPE> front_corner;
extern std::vector<std::array<cv::Point2f,CUBESHAPE> > f_corners;
extern std::vector<std::vector<cv::Point> > down_squares;
extern std::array<cv::Point2f,CUBESHAPE> down_corner;
extern std::vector<std::array<cv::Point2f,CUBESHAPE> > d_corners;
extern std::vector<std::vector<cv::Point> > right_squares;
extern std::array<cv::Point2f,CUBESHAPE> right_corner;
extern std::vector<std::array<cv::Point2f,CUBESHAPE> > r_corners;