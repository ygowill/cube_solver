#include "../include/cube_block.h"

void findRightKeyBlock(std::vector<std::array<cv::Point2f,4> >& corners,int &core_square_index){
    cv::Point2f down_right=corners[0][3];
    for(int i=0;i<corners.size();i++){
        double distance = pow(corners[i][3].x,2)+pow(corners[i][3].y,2);
        if(distance < (pow(down_right.x,2)+pow(down_right.y,2))){
            core_square_index=i;
            down_right = corners[i][3];
        }
    }
}

void findFrontKeyBlock(std::vector<std::array<cv::Point2f,4> >& corners,int &core_square_index){
    cv::Point2f down_lift=corners[0][0];
    for(int i=0;i<corners.size();i++){
        double distance = pow(corners[i][2].x,2)+pow(corners[i][2].y-FRAMESIZE_Y,2);
        if(distance > (pow(down_lift.x,2) + pow(down_lift.y-FRAMESIZE_Y,2))){
            core_square_index=i;
            down_lift = corners[i][2];
        }
    }
}

void findDownKeyBlock(std::vector<std::array<cv::Point2f,4> >& corners,int &core_square_index){
    cv::Point2f top_right=corners[0][0];
    for(int i=0;i<corners.size();i++){
        if(corners[i][1].y > top_right.y){
            core_square_index=i;
            top_right = corners[i][1];
        }
    }
}