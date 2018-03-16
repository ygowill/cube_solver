#include <zconf.h>
#include <fcntl.h>
#include "../include/cube_data.h"
#include "../include/cube_block.h"
#include "../include/cube_corner.h"
#include "../include/cube_squares.h"
#include "../include/cube_bound.h"
#include "../include/color_operation.h"
#include "../include/file_resolution.h"

using namespace cv;
using namespace std;

std::vector<std::vector<cv::Point> > front_squares;
std::array<cv::Point2f,4> front_corner;
std::vector<std::array<cv::Point2f,4> > f_corners;
std::array<char, BLOCKSIZE>f_stickers;
std::vector<std::vector<cv::Point> > down_squares;
std::array<cv::Point2f,4> down_corner;
std::vector<std::array<cv::Point2f,4> > d_corners;
std::array<char, BLOCKSIZE>d_stickers;
std::vector<std::vector<cv::Point> > right_squares;
std::array<cv::Point2f,4> right_corner;
std::vector<std::array<cv::Point2f,4> > r_corners;
std::array<char, BLOCKSIZE>r_stickers;
std::vector<std::vector<cv::Point> > left_squares;
std::array<cv::Point2f,4> left_corner;
std::vector<std::array<cv::Point2f,4> > l_corners;
std::array<char, BLOCKSIZE>l_stickers;
std::vector<std::vector<cv::Point> > up_squares;
std::array<cv::Point2f,4> up_corner;
std::vector<std::array<cv::Point2f,4> > u_corners;
std::array<char, BLOCKSIZE>u_stickers;
std::vector<std::vector<cv::Point> > back_squares;
std::array<cv::Point2f,4> back_corner;
std::vector<std::array<cv::Point2f,4> > b_corners;
std::array<char, BLOCKSIZE>b_stickers;

cv::Point2f pts_dst[]={
    Point(0,0),
    Point(PICSIZE,0),
    Point(0,PICSIZE) ,
    Point(PICSIZE,PICSIZE)
};

cv::Point2f f_remap[4];
cv::Point2f r_remap[4];
cv::Point2f d_remap[4];

string file_path="../res/kociemba";
string file_name="kociemba";
string output="../res/sequence.txt";
string sequence_path="../res/sequence.txt";

void store_result(const char* file_path,array<char, BLOCKSIZE>& stickers){
    FILE* fd=fopen(file_path,"a");
    if(fd==NULL){
        printf("fail to open file.\n");
        exit(1);
    }
    for(auto s:stickers){
        char sticker=s;
        switch (sticker){
            case 'Y':sticker='D';
                break;
            case 'B':sticker='B';
                break;
            case 'O':sticker='L';
                break;
            case 'R':sticker='R';
                break;
            case 'W':sticker='U';
                break;
            case 'G':sticker='F';
                break;
            default:sticker='E';
        }
        fwrite(&sticker, sizeof(char),1,fd);
    }
    fclose(fd);
}

void videoProcess(int camera_number){
    //VideoCapture cap(camera_number); // open webcam

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
    printf("sum: %ld,front:\t%ld\n",squares.size(),front_squares.size());
    printf("sum: %ld,right:\t%ld\n",squares.size(),right_squares.size());
    printf("sum: %ld,down:\t%ld\n",squares.size(),down_squares.size());
    printf("finishing detcetion...\n");
    //addWeighted(mean_frame,0.9,frame,0.1,0,mean_frame);
    mean_frame = frame;
    //imshow("squares",mean_frame);

    /*stop = time(NULL);
    if(stop - start>3){
        break;
    }
    waitKey(1);*/
    //}

    printf("cutting...\n");
    int f_index,r_index,d_index;
    findFrontCorner(front_squares,f_corners);
    findBound(f_corners,front_corner,1);
    findFrontKeyBlock(f_corners,f_index);
    findRightCorner(right_squares,r_corners);
    findBound(r_corners,right_corner,0);
    findRightKeyBlock(r_corners,r_index);
    findDownCorner(down_squares,d_corners);
    findBound(d_corners,down_corner,2);
    findDownKeyBlock(d_corners,d_index);

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
    }*/
    //imshow("Rubik's Detection -ygowill", frame);
    //waitKey(30000);

    /*for(int i=0;i<4;i++){
        circle(frame,Point((int)f_corners[f_index][i].x,(int)f_corners[f_index][i].y),5,Scalar(0,0,0),3);
        circle(frame,Point((int)r_corners[r_index][i].x,(int)r_corners[r_index][i].y),5,Scalar(0,0,0),3);
        circle(frame,Point((int)d_corners[d_index][i].x,(int)d_corners[d_index][i].y),5,Scalar(0,0,0),3);
        circle(frame,Point((int)front_corner[i].x,(int)front_corner[i].y),5,Scalar(0,255,255),3);
        circle(frame,Point((int)right_corner[i].x,(int)right_corner[i].y),5,Scalar(0,255,255),3);
        circle(frame,Point((int)down_corner[i].x,(int)down_corner[i].y),5,Scalar(0,255,255),3);
        //printf("(%d,%d) ",(int)front_corner[i].x,(int)front_corner[i].y);
        //printf("(%d,%d) ",(int)f_corners[index][i].x,(int)f_corners[index][i].y);
    }*/
    //imshow("Rubik's Detection -ygowill", frame);
    //waitKey(60000);

    Mat front_m = getPerspectiveTransform(front_corner.data(),pts_dst);
    Mat front_image;
    warpPerspective(mean_frame,front_image,front_m,mean_frame.size());
    Mat roi_front = front_image(Rect(0,0,PICSIZE,PICSIZE));
    //imshow("roi front",roi_front);
    Mat right_m = getPerspectiveTransform(right_corner.data(),pts_dst);
    Mat right_image;
    warpPerspective(mean_frame,right_image,right_m,mean_frame.size());
    Mat roi_right = right_image(Rect(0,0,PICSIZE,PICSIZE));
    //imshow("roi right",roi_right);
    Mat down_m = getPerspectiveTransform(down_corner.data(),pts_dst);
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

    Mat front_color;
    cube_color_reduce(roi_front,front_color);
    imshow("reduced color",front_color);
    get_cube_color(front_color,f_stickers);
    store_result(sequence_path.c_str(),f_stickers);
    //Mat test_roi=front_color(Rect(150,50,50,50));
    //imshow("test roi",test_roi);
    //printf("color: %c\n",get_block_color(test_roi));

    waitKey(30);
    while(true){
        stop = time(NULL);
        if(stop - start>30){
            break;
        }
    }
}

int main(){
    videoProcess(1);
    //videoProcess(2);
    //TODO add another camera data and combine the two frame data together
    /*string solve_input;
    pid_t pid = fork() ;
    if ( pid < 0 ) {
        return -1;
    } else if ( pid == 0 )  { // child
        close(STDOUT_FILENO);
        open(output.c_str(), O_WRONLY | O_CREAT, 0600);
        execlp(file_path.c_str(), file_name.c_str(), solve_input.c_str(), NULL);
        return -1;
    }
    vector<array<int,2> > servo;
    give_back_sequence(output.c_str(),servo);
    remove(sequence_path.c_str());
    print_servo(servo);*/
    return 0;
}