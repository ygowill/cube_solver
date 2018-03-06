#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "cube_data.h"

void findFrontKeyBlock(std::vector<std::array<cv::Point2f,CUBESHAPE> >& corners,int &core_square_index);
void findRightKeyBlock(std::vector<std::array<cv::Point2f,CUBESHAPE> >& corners,int &core_square_index);
void findDownKeyBlock(std::vector<std::array<cv::Point2f,CUBESHAPE> >& corners,int &core_square_index);