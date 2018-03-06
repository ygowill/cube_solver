#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "cube_data.h"

bool checkExist(std::vector<cv::Point>& square, std::vector<std::vector<cv::Point> >& exist_squares,int maxRange);
static void findSquares( const cv::Mat& image, std::vector<std::vector<cv::Point> >& squares);
static void drawSquares( cv::Mat& image, const std::vector<std::vector<cv::Point> >& squares);