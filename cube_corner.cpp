#include "cube_corner.h"

using namespace std;
using namespace cv;

void findFrontCorner(vector<vector<Point> >& squares, vector<array<Point2f,CUBESHAPE> >& corners){
    Point2f top_left;
    Point2f top_right;
    Point2f down_left;
    Point2f down_right;
    array<Point2f,CUBESHAPE> tmpCorners;

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

void findRightCorner(vector<vector<Point> >& squares, vector<array<Point2f,CUBESHAPE> >& corners){
    Point2f top_left;
    Point2f top_right;
    Point2f down_left;
    Point2f down_right;
    array<Point2f,CUBESHAPE> tmpCorners;

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

void findDownCorner(vector< vector<Point> >& squares, vector<array<Point2f,CUBESHAPE> >& corners){
    Point2f top_left;
    Point2f top_right;
    Point2f down_left;
    Point2f down_right;
    array<Point2f,CUBESHAPE> tmpCorners;

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