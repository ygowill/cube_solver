#include "../include/video.h"

using namespace std;
using namespace cv;

void videoProcess(int camera_number,Cube a){
    VideoCapture cap(camera_number); // open webcam

    /*if (!cap.isOpened()){
        return -1;
    }*/

    Mat frame;
    Mat mean_frame;
    vector<vector<Point> > squares;

    //waitKey(3000);
    //cap >> mean_frame;
    frame = imread("../imgs/input2.jpg");
    resize(frame,frame,Size(frame.cols/4,frame.rows/4));
    //printf("%d",frame.channels());
    //waitKey(10000);
    time_t start,stop;
    start = time(NULL);
    //while (true){
    //cap >> frame;
    //frame = imread("/Users/qinkai/Desktop/cube.JPG");
    if (frame.empty()){
        exit(233);
    }
    printf("detecting...\n");
    findSquares(frame, squares);
    //drawSquares(frame, front_squares);
    //drawSquares(frame, right_squares);
    //drawSquares(frame, down_squares);
    printf("sum: %ld,front:\t%ld\n",squares.size(),a.front_squares.size());
    printf("sum: %ld,right:\t%ld\n",squares.size(),a.right_squares.size());
    printf("sum: %ld,down:\t%ld\n",squares.size(),a.right_squares.size());
    printf("finishing detcetion...\n");
    //addWeighted(mean_frame,0.9,frame,0.1,0,mean_frame);
    mean_frame = frame;
    //imshow("squares",mean_frame);
    //waitKey(30000);

    /*stop = time(NULL);
    if(stop - start>3){
        break;
    }
    waitKey(1);*/
    //}

    printf("cutting...\n");
    int f_index,r_index,d_index;
    findFrontCorner(a.front_squares,a.f_corners);
    findBound(a.f_corners,a.front_corner,1);
    findFrontKeyBlock(a.f_corners,f_index);
    findRightCorner(a.right_squares,a.r_corners);
    findBound(a.r_corners,a.right_corner,0);
    findRightKeyBlock(a.r_corners,r_index);
    findDownCorner(a.down_squares,a.d_corners);
    findBound(a.d_corners,a.down_corner,2);
    findDownKeyBlock(a.d_corners,d_index);

    /*for(int i=0;i<f_corners.size();i++){
        circle(frame,Point((int)f_corners[i][0].x,(int)f_corners[i][0].y),5,Scalar(255,255,255),5);
        circle(frame,Point((int)f_corners[i][1].x,(int)f_corners[i][1].y),5,Scalar(0,0,255),5);
        circle(frame,Point((int)f_corners[i][2].x,(int)f_corners[i][2].y),5,Scalar(0,255,0),5);
        circle(frame,Point((int)f_corners[i][3].x,(int)f_corners[i][3].y),5,Scalar(255,0,255),5);

        circle(frame,Point((int)r_corners[i][0].x,(int)r_corners[i][0].y),5,Scalar(255,255,255),5);
        circle(frame,Point((int)r_corners[i][1].x,(int)r_corners[i][1].y),5,Scalar(0,0,255),5);
        circle(frame,Point((int)r_corners[i][2].x,(int)r_corners[i][2].y),5,Scalar(0,255,0),5);
        circle(frame,Point((int)r_corners[i][3].x,(int)r_corners[i][3].y),5,Scalar(255,0,255),5);

        circle(frame,Point((int)d_corners[i][0].x,(int)d_corners[i][0].y),5,Scalar(255,255,255),5);
        circle(frame,Point((int)d_corners[i][1].x,(int)d_corners[i][1].y),5,Scalar(0,0,255),5);
        circle(frame,Point((int)d_corners[i][2].x,(int)d_corners[i][2].y),5,Scalar(0,255,0),5);
        circle(frame,Point((int)d_corners[i][3].x,(int)d_corners[i][3].y),5,Scalar(255,0,255),5);
    }
    imshow("Rubik's Detection -ygowill", frame);
    waitKey(30000);*/

    /*for(int i=0;i<4;i++){
        circle(frame,Point((int)f_corners[f_index][i].x,(int)f_corners[f_index][i].y),5,Scalar(0,0,0),3);
        circle(frame,Point((int)r_corners[r_index][i].x,(int)r_corners[r_index][i].y),5,Scalar(0,0,0),3);
        circle(frame,Point((int)d_corners[d_index][i].x,(int)d_corners[d_index][i].y),5,Scalar(0,0,0),3);
        circle(frame,Point((int)front_corner[i].x,(int)front_corner[i].y),5,Scalar(0,255,255),3);
        circle(frame,Point((int)right_corner[i].x,(int)right_corner[i].y),5,Scalar(0,255,255),3);
        circle(frame,Point((int)down_corner[i].x,(int)down_corner[i].y),5,Scalar(0,255,255),3);
        //printf("(%d,%d) ",(int)front_corner[i].x,(int)front_corner[i].y);
        //printf("(%d,%d) ",(int)f_corners[index][i].x,(int)f_corners[index][i].y);
    }
    imshow("Rubik's Detection -ygowill", frame);
    waitKey(60000);*/

    Mat front_m = getPerspectiveTransform(a.front_corner.data(),a.pts_dst);
    Mat front_image;
    warpPerspective(mean_frame,front_image,front_m,mean_frame.size());
    Mat roi_front = front_image(Rect(0,0,PICSIZE,PICSIZE));
    //imshow("roi front",roi_front);
    Mat right_m = getPerspectiveTransform(a.right_corner.data(),a.pts_dst);
    Mat right_image;
    warpPerspective(mean_frame,right_image,right_m,mean_frame.size());
    Mat roi_right = right_image(Rect(0,0,PICSIZE,PICSIZE));
    //imshow("roi right",roi_right);
    Mat down_m = getPerspectiveTransform(a.down_corner.data(),a.pts_dst);
    Mat down_image;
    warpPerspective(mean_frame,down_image,down_m,mean_frame.size());
    Mat roi_down = down_image(Rect(0,0,PICSIZE,PICSIZE));
    //imshow("roi down",roi_down);
    //waitKey(60000);
    printf("processing done...\n");


    /*Point2f src[] = {
        Point(0,0),
        Point(PICSIZE,0),
        Point(0,PICSIZE) ,
        Point(PICSIZE,PICSIZE)
    };
    front_m = getPerspectiveTransform(test,pts_dst);
    warpPerspective(roi_front,roi_front,front_m,roi_front.size());
    imshow("roi front",roi_front);
    waitKey(30000);*/

    Mat right_color;
    cube_color_reduce(roi_right,right_color);
    imshow("reduced color",right_color);
    get_cube_color(right_color,a.r_stickers);

    store_result(sequence_path.c_str(),a.r_stickers);
    //Mat test_roi=front_color(Rect(150,50,50,50));
    //imshow("test roi",test_roi);
    //printf("color: %c\n",get_block_color(test_roi));

    /*waitKey(30);
    while(true){
        stop = time(NULL);
        if(stop - start>30){
            break;
        }
    }*/
}