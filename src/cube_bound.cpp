#include "../include/cube_bound.h"

using namespace std;
using namespace cv;

void number_signal(cv::Point2f src,cv::Point2f dst,int sig[]){
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

void findBound(std::vector<std::array<cv::Point2f,4> >& corners,std::array<cv::Point2f,4>& bounds,int mode){
    int core_square_index=0;
    switch(mode){
        case 1:findFrontKeyBlock(corners,core_square_index);
            break;
        case 0:findRightKeyBlock(corners,core_square_index);
            break;
        case 2:findDownKeyBlock(corners,core_square_index);
            break;
        default: exit(0);
    }

    cv::Point2f keyCorner[4];
    for(int i=0;i<4;i++){
        keyCorner[i]=corners.at((unsigned long)core_square_index)[i];
    }
    float key_x = abs(keyCorner[0].x+keyCorner[2].x-keyCorner[1].x-keyCorner[3].x)/2;
    float key_y = abs(keyCorner[0].y+keyCorner[1].y-keyCorner[2].y-keyCorner[3].y)/2;
    float key_dx = abs(keyCorner[1].x+keyCorner[0].x-keyCorner[2].x-keyCorner[3].x)/2;
    float key_dy = abs(keyCorner[1].y+keyCorner[3].y-keyCorner[0].y-keyCorner[2].y)/2;

    int sig[2];
    switch(mode){
        case 0:
            number_signal(keyCorner[0],keyCorner[2],sig);
            bounds[2].x=keyCorner[2].x+sig[0]*(CUBESHAPE-1)*(key_dx+RIGHT_DISTANCE_COMPENSATION_X);
            bounds[2].y=keyCorner[2].y+sig[1]*(CUBESHAPE-1)*(key_y+RIGHT_DISTANCE_COMPENSATION_Y);
            bounds[0].x=keyCorner[0].x;
            bounds[0].y=keyCorner[0].y;
            number_signal(keyCorner[0],keyCorner[1],sig);
            bounds[1].x=keyCorner[1].x+sig[0]*(CUBESHAPE-1)*(key_x+RIGHT_DISTANCE_COMPENSATION_X);
            bounds[1].y=keyCorner[1].y+sig[1]*(CUBESHAPE-1)*(key_dy+RIGHT_DISTANCE_COMPENSATION_Y);

            bounds[3].x=bounds[1].x+bounds[2].x-keyCorner[0].x+RIGHT_DISTANCE_COMPENSATION_XY_X;
            bounds[3].y=bounds[1].y+bounds[2].y-keyCorner[0].y+RIGHT_DISTANCE_COMPENSATION_XY_Y;
            break;
        case 2:
            number_signal(keyCorner[2],keyCorner[0],sig);
            bounds[0].x=keyCorner[0].x+sig[0]*(CUBESHAPE-1)*(key_dx+DOWN_DISTANCE_COMPENSATION_X);
            bounds[0].y=keyCorner[0].y+sig[1]*(CUBESHAPE-1)*(key_y+DOWN_DISTANCE_COMPENSATION_Y);
            bounds[2].x=keyCorner[2].x;
            bounds[2].y=keyCorner[2].y;
            number_signal(keyCorner[2],keyCorner[3],sig);
            bounds[3].x=keyCorner[3].x+sig[0]*(CUBESHAPE-1)*(key_x+DOWN_DISTANCE_COMPENSATION_X);
            bounds[3].y=keyCorner[3].y+sig[1]*(CUBESHAPE-1)*(key_dy+DOWN_DISTANCE_COMPENSATION_Y);

            bounds[1].x=bounds[0].x+bounds[3].x-keyCorner[2].x+DOWN_DISTANCE_COMPENSATION_XY_X;
            bounds[1].y=bounds[0].y+bounds[3].y-keyCorner[2].y+DOWN_DISTANCE_COMPENSATION_XY_Y;
            break;
        case 1:number_signal(keyCorner[1],keyCorner[3],sig);
            bounds[3].x=keyCorner[3].x+sig[0]*(CUBESHAPE-1)*(key_dx+FRONT_DISTANCE_COMPENSATION_X);
            bounds[3].y=keyCorner[3].y+sig[1]*(CUBESHAPE-1)*(key_y+FRONT_DISTANCE_COMPENSATION_Y);
            bounds[1].x=keyCorner[1].x;
            bounds[1].y=keyCorner[1].y;
            number_signal(keyCorner[1],keyCorner[0],sig);
            bounds[0].x=keyCorner[0].x+sig[0]*(CUBESHAPE-1)*(key_x+FRONT_DISTANCE_COMPENSATION_X);
            bounds[0].y=keyCorner[0].y+sig[1]*(CUBESHAPE-1)*(key_dy+FRONT_DISTANCE_COMPENSATION_X);

            bounds[2].x=bounds[0].x+bounds[3].x-keyCorner[1].x+FRONT_DISTANCE_COMPENSATION_XY_X;
            bounds[2].y=bounds[0].y+bounds[3].y-keyCorner[1].y+FRONT_DISTANCE_COMPENSATION_XY_Y;
            break;
    }
}

Point cross_point(Point p1,Point p2,Point p3,Point p4){
    double x_member, x_denominator, y_member, y_denominator;
    Point cross_point;
    x_denominator = p4.x*p2.y - p4.x*p1.y - p3.x*p2.y + p3.x*p1.y
        - p2.x*p4.y + p2.x*p3.y + p1.x*p4.y - p1.x*p3.y;

    x_member = p3.y*p4.x*p2.x - p4.y*p3.x*p2.x - p3.y*p4.x*p1.x + p4.y*p3.x*p1.x
        - p1.y*p2.x*p4.x + p2.y*p1.x*p4.x + p1.y*p2.x*p3.x - p2.y*p1.x*p3.x;

    if (x_denominator == 0){
        cross_point.x = 0;
    }
    else{
        cross_point.x = (int)(x_member / x_denominator);
    }

    y_denominator = p4.y*p2.x - p4.y*p1.x - p3.y*p2.x + p1.x*p3.y
        - p2.y*p4.x + p2.y*p3.x + p1.y*p4.x - p1.y*p3.x;

    y_member = -p3.y*p4.x*p2.y + p4.y*p3.x*p2.y + p3.y*p4.x*p1.y - p4.y*p3.x*p1.y
        + p1.y*p2.x*p4.y - p1.y*p2.x*p3.y - p2.y*p1.x*p4.y + p2.y*p1.x*p3.y;

    if (y_denominator == 0){
        cross_point.y = 0;
    }
    else{
        cross_point.y = (int)(y_member / y_denominator);
    }

    return cross_point;
}

Point reMapBound(Mat roi_img){
    vector<Vec4i> lines;
    array<Vec4i,2> stored_line;
    Point point1,point2;
    float x_min=300,y_min=300;
    Mat gray_roi;
    GaussianBlur(roi_img,roi_img,Size(35,35),0,0);
    //imshow("front roi",roi_img);
    cvtColor(roi_img,gray_roi,COLOR_BGR2GRAY);
    HoughLinesP(gray_roi,lines,400,20*CV_PI/180,60,60,20);

    for (size_t i = 0; i < lines.size(); i++){
        point1 = Point(lines[i][0], lines[i][1]);
        point2 = Point(lines[i][2], lines[i][3]);
        if(point1.x!=point2.x && (pow(point1.x-point2.x,2)+pow(point1.y-point2.y,2)>1000)){
            //line(roi_front, point1,point2,Scalar(0, 0, 0), 1 , CV_AA);
            float k=abs(point1.y-point2.y)/abs(point1.x-point2.x);
            if(k>1){
                line(roi_img, point1,point2,Scalar(255, 0, 0), 1 , CV_AA);
                if(point1.x < point2.x){
                    if(point2.x < x_min){
                        x_min=point2.x;
                        stored_line[0]=lines[i];
                    }
                }
                else{
                    if(point1.x < x_min){
                        x_min=point1.x;
                        stored_line[0]=lines[i];
                    }
                }
            }
            else{
                line(roi_img, point1,point2,Scalar(0, 255, 0), 1 , CV_AA);
                if(point1.y > point2.y){
                    if(point1.y < y_min){
                        y_min=point1.y;
                        stored_line[1]=lines[i];
                    }
                }
                else{
                    if(point2.y < y_min){
                        y_min=point2.y;
                        stored_line[1]=lines[i];
                    }
                }
            }
        }
    }
    //line(roi_img, Point(stored_line[0][0],stored_line[0][1]), Point(stored_line[0][2],stored_line[0][3]),Scalar(0, 0, 255), 3 , CV_AA);
    //line(roi_img, Point(stored_line[1][0],stored_line[1][1]), Point(stored_line[1][2],stored_line[1][3]),Scalar(0, 0, 255), 3 , CV_AA);
    Point cross_p=cross_point(Point(stored_line[0][0],stored_line[0][1]), Point(stored_line[0][2],stored_line[0][3]),
                              Point(stored_line[1][0],stored_line[1][1]), Point(stored_line[1][2],stored_line[1][3]));
    //circle(roi_img,cross_p,2,Scalar(0,0,255),2,LINE_AA);
    //imshow("roi front",roi_img);
    return cross_p;
}