#include "../include/video.h"

using namespace std;
using namespace cv;

void videoProcess(Cube& cube){
    VideoCapture cap(cube.cameraID); // open webcam

    if (!cap.isOpened()){
        exit(0);
    }

    Mat frame,mean_frame;
    vector<vector<Point> > squares;

    waitKey(2000);
    //frame = imread("../imgs/input2.jpg");
    //printf("%d",frame.channels());
    //waitKey(10000);
    cap >> frame >> mean_frame;
    resize(mean_frame,mean_frame,Size(mean_frame.cols/2,mean_frame.rows/2));
    time_t start,stop;
    start = time(NULL);
    while (true){
        cap >> frame;
        resize(frame,frame,Size(frame.cols/2,frame.rows/2));
        //frame = imread("/Users/qinkai/Desktop/cube.JPG");
        if (frame.empty()){
            exit(233);
        }
        printf("detecting...\n");
        findSquares(mean_frame, cube);
        //drawSquares(frame, cube.front_squares);
        //drawSquares(frame, cube.right_squares);
        //drawSquares(frame, cube.down_squares);
        printf("front:\t%ld\n",cube.front_squares.size());
        printf("right:\t%ld\n",cube.right_squares.size());
        printf("down:\t%ld\n",cube.down_squares.size());
        printf("finishing detcetion...\n");
        addWeighted(mean_frame,0.9,frame,0.1,0,mean_frame);
        //imshow("frame test",frame);
        //waitKey(30000);

        stop = time(NULL);
        if(stop - start > 3 ){
            break;
        }
    }

    printf("cutting...\n");
    findFrontCorner(cube.front_squares,cube.f_corners);
    findBound(cube.f_corners,cube.front_corner,1);
    findFrontKeyBlock(cube.f_corners,cube.f_index);
    findRightCorner(cube.right_squares,cube.r_corners);
    findBound(cube.r_corners,cube.right_corner,0);
    findRightKeyBlock(cube.r_corners,cube.r_index);
    findDownCorner(cube.down_squares,cube.d_corners);
    findBound(cube.d_corners,cube.down_corner,2);
    findDownKeyBlock(cube.d_corners,cube.d_index);

    /*for(int i=0;i<cube.f_corners.size();i++){
        circle(mean_frame,Point((int)cube.f_corners[i][0].x,(int)cube.f_corners[i][0].y),5,Scalar(255,255,255),5);
        circle(mean_frame,Point((int)cube.f_corners[i][1].x,(int)cube.f_corners[i][1].y),5,Scalar(0,0,255),5);
        circle(mean_frame,Point((int)cube.f_corners[i][2].x,(int)cube.f_corners[i][2].y),5,Scalar(0,255,0),5);
        circle(mean_frame,Point((int)cube.f_corners[i][3].x,(int)cube.f_corners[i][3].y),5,Scalar(255,0,255),5);
    }
    for(int i=0;i<cube.r_corners.size();i++){
        circle(mean_frame,Point((int)cube.r_corners[i][0].x,(int)cube.r_corners[i][0].y),5,Scalar(255,255,255),5);
        circle(mean_frame,Point((int)cube.r_corners[i][1].x,(int)cube.r_corners[i][1].y),5,Scalar(0,0,255),5);
        circle(mean_frame,Point((int)cube.r_corners[i][2].x,(int)cube.r_corners[i][2].y),5,Scalar(0,255,0),5);
        circle(mean_frame,Point((int)cube.r_corners[i][3].x,(int)cube.r_corners[i][3].y),5,Scalar(255,0,255),5);
    }
    for(int i=0;i<cube.d_corners.size();i++){
        circle(mean_frame,Point((int)cube.d_corners[i][0].x,(int)cube.d_corners[i][0].y),5,Scalar(255,255,255),5);
        circle(mean_frame,Point((int)cube.d_corners[i][1].x,(int)cube.d_corners[i][1].y),5,Scalar(0,0,255),5);
        circle(mean_frame,Point((int)cube.d_corners[i][2].x,(int)cube.d_corners[i][2].y),5,Scalar(0,255,0),5);
        circle(mean_frame,Point((int)cube.d_corners[i][3].x,(int)cube.d_corners[i][3].y),5,Scalar(255,0,255),5);
    }*/
    //imshow("Rubik's Detection -ygowill", mean_frame);
    //waitKey(30000);

    /*for(int i=0;i<4;i++){
        //circle(mean_frame,Point((int)cube.f_corners[cube.f_index][i].x,(int)cube.f_corners[cube.f_index][i].y),5,Scalar(0,0,0),3);
        //circle(mean_frame,Point((int)cube.r_corners[cube.r_index][i].x,(int)cube.r_corners[cube.r_index][i].y),5,Scalar(0,0,0),3);
        //circle(mean_frame,Point((int)cube.d_corners[cube.d_index][i].x,(int)cube.d_corners[cube.d_index][i].y),5,Scalar(0,0,0),3);
        //circle(mean_frame,Point((int)cube.front_corner[i].x,(int)cube.front_corner[i].y),5,Scalar(0,255,255),3);
        //circle(mean_frame,Point((int)cube.right_corner[i].x,(int)cube.right_corner[i].y),5,Scalar(0,255,255),3);
        circle(mean_frame,Point((int)cube.down_corner[i].x,(int)cube.down_corner[i].y),5,Scalar(0,255,255),3);
        //printf("(%d,%d) ",(int)front_corner[i].x,(int)front_corner[i].y);
        //printf("(%d,%d) ",(int)f_corners[index][i].x,(int)f_corners[index][i].y);
    }
    imshow("Rubik's Detection -ygowill", mean_frame);
    waitKey(30000);*/

    Point2f pts_dst[] = {
        Point(0,0),
        Point(PICSIZE,0),
        Point(0,PICSIZE) ,
        Point(PICSIZE,PICSIZE)
    };
    Mat front_m = getPerspectiveTransform(cube.front_corner.data(),pts_dst);
    Mat front_image;
    warpPerspective(mean_frame,front_image,front_m,mean_frame.size());
    Mat roi_front = front_image(Rect(0,0,PICSIZE,PICSIZE));
    imshow("roi front",roi_front);
    Mat right_m = getPerspectiveTransform(cube.right_corner.data(),pts_dst);
    Mat right_image;
    warpPerspective(mean_frame,right_image,right_m,mean_frame.size());
    Mat roi_right = right_image(Rect(0,0,PICSIZE,PICSIZE));
    imshow("roi right",roi_right);
    Mat down_m = getPerspectiveTransform(cube.down_corner.data(),pts_dst);
    Mat down_image;
    warpPerspective(mean_frame,down_image,down_m,mean_frame.size());
    Mat roi_down = down_image(Rect(0,0,PICSIZE,PICSIZE));
    imshow("roi down",roi_down);
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

    Mat right_color,front_color,down_color;

    cube_color_reduce(roi_right,right_color);
    imshow("reduced right color",right_color);
    get_cube_color(right_color,cube.r_stickers);

    cube_color_reduce(roi_front,front_color);
    imshow("reduced front color",front_color);
    get_cube_color(front_color,cube.f_stickers);

    cube_color_reduce(roi_down,down_color);
    imshow("reduced down color",down_color);
    get_cube_color(down_color,cube.d_stickers);
    waitKey(60000);
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