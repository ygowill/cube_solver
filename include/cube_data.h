#pragma once

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

const int MAXRANGE = 1000;
const int MAXTAN = 3;
const int PICSIZE = 200;
const int CUBESHAPE = 3;
const int STICKERSIZE = PICSIZE/CUBESHAPE;
const int FRAMESIZE_X = 1280;
const int FRAMESIZE_Y = 720;
const int BLOCKSIZE = CUBESHAPE*CUBESHAPE;

const int FRONT_DISTANCE_COMPENSATION_X = 7;
const int FRONT_DISTANCE_COMPENSATION_Y = 7;
const int FRONT_DISTANCE_COMPENSATION_XY_X = 40;
const int FRONT_DISTANCE_COMPENSATION_XY_Y = -10;

const int RIGHT_DISTANCE_COMPENSATION_X = 7;
const int RIGHT_DISTANCE_COMPENSATION_Y = 3;
const int RIGHT_DISTANCE_COMPENSATION_XY_X = -20;
const int RIGHT_DISTANCE_COMPENSATION_XY_Y = -10;

const int DOWN_DISTANCE_COMPENSATION_X = 10;
const int DOWN_DISTANCE_COMPENSATION_Y = 0;
const int DOWN_DISTANCE_COMPENSATION_XY_X = 0;
const int DOWN_DISTANCE_COMPENSATION_XY_Y = 20;

const int RED = 0;
const int ORANGE = 13;
const int YELLOW = 31;
const int GREEN = 75;
const int BLUE = 125;
const int WHITE_S = 0;

struct cube_struct{
  int cameraID;
  std::vector<std::vector<cv::Point> > front_squares;
  std::array<cv::Point2f,4> front_corner;
  std::vector<std::array<cv::Point2f,4> > f_corners;
  int f_index;
  std::array<char, BLOCKSIZE>f_stickers;
  std::vector<std::vector<cv::Point> > down_squares;
  std::array<cv::Point2f,4> down_corner;
  std::vector<std::array<cv::Point2f,4> > d_corners;
  int d_index;
  std::array<char, BLOCKSIZE>d_stickers;
  std::vector<std::vector<cv::Point> > right_squares;
  std::array<cv::Point2f,4> right_corner;
  std::vector<std::array<cv::Point2f,4> > r_corners;
  int r_index;
  std::array<char, BLOCKSIZE>r_stickers;
};

typedef struct cube_struct Cube;

const std::string sequence_path="../res/sequence.txt";
const std::string file_path="../res/kociemba";
const std::string file_name="kociemba";
const std::string output="../res/output.txt";
