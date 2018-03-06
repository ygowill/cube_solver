#include "cube_bound.h"

using namespace std;
using namespace cv;

void number_signal(Point2f src,Point2f dst,int sig[]){
    if(dst.x >= src.x){
        sig[0]=1;
    }
    else{
        sig[0]=-1;
    }
    if(dst.y >= src.y){
        sig[1]=1;
    }
    else{
        sig[1]=-1;
    }
}

void findBound(vector<array<Point2f,CUBESHAPE> >& corners,array<Point2f,CUBESHAPE>& bounds,int mode){
    int core_square_index=0;
    switch(mode){
        case 3:findFrontKeyBlock(corners,core_square_index);
            break;
        case 2:findRightKeyBlock(corners,core_square_index);
            break;
        case 1:findDownKeyBlock(corners,core_square_index);
            break;
        default: exit(0);
    }

    Point2f keyCorner[4];
    for(int i=0;i<4;i++){
        keyCorner[i]=corners.at((unsigned long)core_square_index)[i];
    }
    float key_x = abs(keyCorner[0].x+keyCorner[2].x-keyCorner[1].x-keyCorner[3].x)/2;
    float key_y = abs(keyCorner[0].y+keyCorner[1].y-keyCorner[2].y-keyCorner[3].y)/2;
    float key_dx = abs(keyCorner[1].x+keyCorner[0].x-keyCorner[2].x-keyCorner[3].x)/2;
    float key_dy = abs(keyCorner[1].y+keyCorner[3].y-keyCorner[0].y-keyCorner[2].y)/2;

    int sig[2];
    switch(mode){
        case 3:
            number_signal(keyCorner[3],keyCorner[1],sig);
            bounds[1].x=keyCorner[1].x+sig[0]*(CUBESHAPE-1)*(key_dx+FRONT_DISTANCE_COMPENSATION_X);
            bounds[1].y=keyCorner[1].y+sig[1]*(CUBESHAPE-1)*(key_y+FRONT_DISTANCE_COMPENSATION_Y);
            bounds[3].x=keyCorner[3].x;
            bounds[3].y=keyCorner[3].y;
            number_signal(keyCorner[3],keyCorner[2],sig);
            bounds[2].x=keyCorner[2].x+sig[0]*(CUBESHAPE-1)*(key_x+FRONT_DISTANCE_COMPENSATION_X);
            bounds[2].y=keyCorner[2].y+sig[1]*(CUBESHAPE-1)*(key_dy+FRONT_DISTANCE_COMPENSATION_Y);

            bounds[0].x=bounds[1].x+bounds[2].x-keyCorner[3].x+FRONT_DISTANCE_COMPENSATION_XY_X;
            bounds[0].y=bounds[1].y+bounds[2].y-keyCorner[3].y+FRONT_DISTANCE_COMPENSATION_XY_Y;
            break;
        case 2:
            number_signal(keyCorner[2],keyCorner[0],sig);
            bounds[0].x=keyCorner[0].x+sig[0]*(CUBESHAPE-1)*(key_dx+RIGHT_DISTANCE_COMPENSATION_X);
            bounds[0].y=keyCorner[0].y+sig[1]*(CUBESHAPE-1)*(key_y+RIGHT_DISTANCE_COMPENSATION_Y);
            bounds[2].x=keyCorner[2].x;
            bounds[2].y=keyCorner[2].y;
            number_signal(keyCorner[2],keyCorner[3],sig);
            bounds[3].x=keyCorner[3].x+sig[0]*(CUBESHAPE-1)*(key_x+RIGHT_DISTANCE_COMPENSATION_X);
            bounds[3].y=keyCorner[3].y+sig[1]*(CUBESHAPE-1)*(key_dy+RIGHT_DISTANCE_COMPENSATION_Y);

            bounds[1].x=bounds[0].x+bounds[3].x-keyCorner[2].x+RIGHT_DISTANCE_COMPENSATION_XY_X;
            bounds[1].y=bounds[0].y+bounds[3].y-keyCorner[2].y+RIGHT_DISTANCE_COMPENSATION_XY_Y;
            break;
        case 1:number_signal(keyCorner[1],keyCorner[0],sig);
            bounds[0].x=keyCorner[0].x+sig[0]*(CUBESHAPE-1)*(key_dx+DOWN_DISTANCE_COMPENSATION_X);
            bounds[0].y=keyCorner[0].y+sig[1]*(CUBESHAPE-1)*(key_y+DOWN_DISTANCE_COMPENSATION_Y);
            bounds[1].x=keyCorner[1].x;
            bounds[1].y=keyCorner[1].y;
            number_signal(keyCorner[1],keyCorner[3],sig);
            bounds[3].x=keyCorner[3].x+sig[0]*(CUBESHAPE-1)*(key_x+DOWN_DISTANCE_COMPENSATION_X);
            bounds[3].y=keyCorner[3].y+sig[1]*(CUBESHAPE-1)*(key_dy+DOWN_DISTANCE_COMPENSATION_Y);

            bounds[2].x=bounds[0].x+bounds[3].x-keyCorner[1].x+DOWN_DISTANCE_COMPENSATION_XY_X;
            bounds[2].y=bounds[0].y+bounds[3].y-keyCorner[1].y+DOWN_DISTANCE_COMPENSATION_XY_Y;
            break;
        default:exit(0);
    }
}