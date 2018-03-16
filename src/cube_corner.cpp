#include "../include/cube_corner.h"

void findRightCorner(std::vector<std::vector<cv::Point> >& squares, std::vector<std::array<cv::Point2f,4> >& corners){
    cv::Point2f top_left;
    cv::Point2f top_right;
    cv::Point2f down_left;
    cv::Point2f down_right;
    std::array<cv::Point2f,4> tmpCorners;

    for(int i=0;i<squares.size();i++){
        top_left=squares[i][0];
        top_right=squares[i][0];
        down_left=squares[i][0];
        down_right=squares[i][0];
        if((pow(squares[i][0].x-squares[i][2].x,2)+pow(squares[i][0].y-squares[i][2].y,2)) >
            pow(squares[i][1].x-squares[i][3].x,2)+pow(squares[i][1].y-squares[i][3].y,2)){
            if(squares[i][0].x > squares[i][2].x){
                top_right=squares[i][0];
                down_left=squares[i][2];
            }
            else{
                down_left=squares[i][0];
                top_right=squares[i][2];
            }
            if(squares[i][1].y > squares[i][3].y){
                down_right=squares[i][1];
                top_left=squares[i][3];
            }
            else{
                top_left=squares[i][1];
                down_right=squares[i][3];
            }
        }
        else{
            if(squares[i][1].x > squares[i][3].x){
                top_right=squares[i][1];
                down_left=squares[i][3];
            }
            else{
                down_left=squares[i][1];
                top_right=squares[i][3];
            }
            if(squares[i][0].y > squares[i][2].y){
                down_right=squares[i][0];
                top_left=squares[i][2];
            }
            else{
                top_left=squares[i][0];
                down_right=squares[i][2];
            }
        }
        tmpCorners[0]=top_left;
        tmpCorners[1]=top_right;
        tmpCorners[2]=down_left;
        tmpCorners[3]=down_right;
        corners.push_back(tmpCorners);
    }
}

void findFrontCorner(std::vector<std::vector<cv::Point> >& squares, std::vector<std::array<cv::Point2f,4> >& corners){
    cv::Point2f top_left;
    cv::Point2f top_right;
    cv::Point2f down_left;
    cv::Point2f down_right;
    std::array<cv::Point2f,4> tmpCorners;

    for(int i=0;i<squares.size();i++){
        top_left=squares[i][0];
        top_right=squares[i][0];
        down_left=squares[i][0];
        down_right=squares[i][0];
        if((pow(squares[i][0].x-squares[i][2].x,2)+pow(squares[i][0].y-squares[i][2].y,2)) >
            pow(squares[i][1].x-squares[i][3].x,2)+pow(squares[i][1].y-squares[i][3].y,2)){
            if(squares[i][0].y > squares[i][2].y){
                down_right=squares[i][0];
                top_left=squares[i][2];
            }
            else{
                top_left=squares[i][0];
                down_right=squares[i][2];
            }
            if(squares[i][1].x > squares[i][3].x){
                top_right=squares[i][1];
                down_left=squares[i][3];
            }
            else{
                down_left=squares[i][1];
                top_right=squares[i][3];
            }
        }
        else{
            if(squares[i][1].y > squares[i][3].y){
                down_right=squares[i][1];
                top_left=squares[i][3];
            }
            else{
                top_left=squares[i][1];
                down_right=squares[i][3];
            }
            if(squares[i][0].x > squares[i][2].x){
                top_right=squares[i][0];
                down_left=squares[i][2];
            }
            else{
                down_left=squares[i][0];
                top_right=squares[i][2];
            }
        }
        tmpCorners[0]=top_left;
        tmpCorners[1]=top_right;
        tmpCorners[2]=down_left;
        tmpCorners[3]=down_right;
        corners.push_back(tmpCorners);
    }
}

void findDownCorner(std::vector< std::vector<cv::Point> >& squares, std::vector<std::array<cv::Point2f,4> >& corners){
    cv::Point2f top_left;
    cv::Point2f top_right;
    cv::Point2f down_left;
    cv::Point2f down_right;
    std::array<cv::Point2f,4> tmpCorners;

    for(int i=0;i<squares.size();i++){
        top_left=squares[i][0];
        top_right=squares[i][0];
        down_left=squares[i][0];
        down_right=squares[i][0];
        if((pow(squares[i][0].x-squares[i][2].x,2)+pow(squares[i][0].y-squares[i][2].y,2)) >
            pow(squares[i][1].x-squares[i][3].x,2)+pow(squares[i][1].y-squares[i][3].y,2)){
            if(squares[i][0].x < squares[i][2].x){
                top_left=squares[i][0];
                down_right=squares[i][2];
            }
            else{
                down_right=squares[i][0];
                top_left=squares[i][2];
            }
            if(squares[i][1].y < squares[i][3].y){
                top_right=squares[i][1];
                down_left=squares[i][3];
            }
            else{
                down_left=squares[i][1];
                top_right=squares[i][3];
            }
        }
        else{
            if(squares[i][1].x < squares[i][3].x){
                top_left=squares[i][1];
                down_right=squares[i][3];
            }
            else{
                down_right=squares[i][1];
                top_left=squares[i][3];
            }
            if(squares[i][0].y < squares[i][2].y){
                top_right=squares[i][0];
                down_left=squares[i][2];
            }
            else{
                down_left=squares[i][0];
                top_right=squares[i][2];
            }
        }
        tmpCorners[0]=top_left;
        tmpCorners[1]=top_right;
        tmpCorners[2]=down_left;
        tmpCorners[3]=down_right;
        corners.push_back(tmpCorners);
    }
}