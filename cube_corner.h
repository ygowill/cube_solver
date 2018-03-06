#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "cube_data.h"

void findFrontCorner(std::vector<std::vector<cv::Point> >& squares, std::vector<std::array<cv::Point2f,CUBESHAPE> >& corners);
void findRightCorner(std::vector<std::vector<cv::Point> >& squares, std::vector<std::array<cv::Point2f,CUBESHAPE> >& corners);
void findDownCorner(std::vector<std::vector<cv::Point> >& squares, std::vector<std::array<cv::Point2f,CUBESHAPE> >& corners);