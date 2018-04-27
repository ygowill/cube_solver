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

const int FRONT_DISTANCE_COMPENSATION_X = 9;
const int FRONT_DISTANCE_COMPENSATION_Y = 9;
const int FRONT_DISTANCE_COMPENSATION_XY_X = 0;
const int FRONT_DISTANCE_COMPENSATION_XY_Y = 0;

const int RIGHT_DISTANCE_COMPENSATION_X = 10;
const int RIGHT_DISTANCE_COMPENSATION_Y = 10;
const int RIGHT_DISTANCE_COMPENSATION_XY_X = -30;
const int RIGHT_DISTANCE_COMPENSATION_XY_Y = -10;

const int DOWN_DISTANCE_COMPENSATION_X = 15;
const int DOWN_DISTANCE_COMPENSATION_Y = 10;
const int DOWN_DISTANCE_COMPENSATION_XY_X = 10;
const int DOWN_DISTANCE_COMPENSATION_XY_Y = 40;
const int RED = 0;
const int ORANGE = 13;
const int YELLOW = 31;
const int GREEN = 75;
const int BLUE = 125;
const int WHITE_S = 0;


#ifndef CUBE_SOLVER_CUBE_DATA
#define CUBE_SOLVER_CUBE_DATA

extern std::vector<std::vector<cv::Point> > front_squares;
extern std::array<cv::Point2f,4> front_corner;
extern std::vector<std::array<cv::Point2f,4> > f_corners;
extern std::array<char, BLOCKSIZE>f_stickers;
extern std::vector<std::vector<cv::Point> > down_squares;
extern std::array<cv::Point2f,4> down_corner;
extern std::vector<std::array<cv::Point2f,4> > d_corners;
extern std::array<char, BLOCKSIZE>d_stickers;
extern std::vector<std::vector<cv::Point> > right_squares;
extern std::array<cv::Point2f,4> right_corner;
extern std::vector<std::array<cv::Point2f,4> > r_corners;
extern std::array<char, BLOCKSIZE>r_stickers;
extern std::vector<std::vector<cv::Point> > left_squares;
extern std::array<cv::Point2f,4> left_corner;
extern std::vector<std::array<cv::Point2f,4> > l_corners;
extern std::array<char, BLOCKSIZE>l_stickers;
extern std::vector<std::vector<cv::Point> > up_squares;
extern std::array<cv::Point2f,4> up_corner;
extern std::vector<std::array<cv::Point2f,4> > u_corners;
extern std::array<char, BLOCKSIZE>u_stickers;
extern std::vector<std::vector<cv::Point> > back_squares;
extern std::array<cv::Point2f,4> back_corner;
extern std::vector<std::array<cv::Point2f,4> > b_corners;
extern std::array<char, BLOCKSIZE>b_stickers;

extern cv::Point2f pts_dst[];
extern cv::Point2f f_remap[];
extern cv::Point2f r_remap[];
extern cv::Point2f d_remap[];

#endif //CUBE_SOLVER_CUBE_DATA

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
