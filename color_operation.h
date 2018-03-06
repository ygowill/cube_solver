#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

void cube_color_reduce(cv::Mat& src, cv::Mat& dst);
void my_kmeans(cv::Mat& src,cv::Mat& dst,int clusterCount,int attempts)