#include "cube_squares.h"

using namespace std;
using namespace cv;

static void drawSquares( Mat& image, const vector<vector<Point> >& squares ){
    for( size_t i = 0; i < squares.size(); i++ ){
        const Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        int shift = 1;

        Rect r=boundingRect( Mat(squares[i]));
        Mat roi = image(r);
        Scalar color = mean(roi);
        polylines(image, &p, &n, 1, true, Scalar(0,0,0), 2, LINE_AA, shift);
        fillPoly(image, &p, &n, 1, color, LINE_AA, shift);
    }
}

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
static void findSquares( const Mat& image, vector<vector<Point> >& squares){
    squares.clear();
    Mat gray,gray0,color_gray,image_clone,reduced;
    vector<vector<Point> > contours;

    vector<Vec4i> lines;
    //Point point1, point2;
    //use k-means to do color quantization
    /*cvtColor(image,image_clone,COLOR_BGR2HSV);
    colorReduce(image_clone,reduced,32);
    imshow("color reduce result",reduced);*/
    cvtColor(image,gray0,COLOR_BGR2GRAY);
    GaussianBlur(gray0, gray0, Size(9,9), 0, 0);

    //pyrMeanShiftFiltering(image,image,spatialRad,colorRad,maxPryLevel);
    //cvtColor(image,gray0,COLOR_BGR2GRAY);
    Canny(gray0,gray, 0, 30, 3);
    /*HoughLinesP(gray,lines,1,CV_PI/180,35,35,15);

    for (size_t i = 0; i < lines.size(); i++){
        point1 = Point(lines[i][0], lines[i][1]);
        point2 = Point(lines[i][2], lines[i][3]);
        line(image, point1, point2, Scalar(255, 255, 255), 3 , CV_AA);
    }*/
    imshow("canny result",gray);

    // find contours and store them all as a list
    findContours(gray, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<Point> approx;

    // test each contour
    for( size_t i = 0; i < contours.size(); i++ ){
        // approximate contour with accuracy proportional
        // to the contour perimeter
        approxPolyDP(Mat(contours[i]), approx, 12, true);

        // square contours should have 4 vertices after approximation
        // relatively large area (to filter out noisy contours)
        // and be convex.
        // Note: absolute value of an area is used because
        // area may be positive or negative - in accordance with the
        // contour orientation
        if( approx.size() == 4 &&
            fabs(contourArea(Mat(approx))) > 1000 &&
            isContourConvex(Mat(approx)) ){
            squares.push_back(approx);
            int dx1=approx[0].x-approx[2].x;
            int dy1=approx[0].y-approx[2].y;
            int dx2=approx[1].x-approx[3].x;
            int dy2=approx[1].y-approx[3].y;
            if(pow(dx1,2)+pow(dy1,2) >= pow(dx2,2)+pow(dy2,2) ){
                if(dy1/dx1 < MAXTAN  && dy1/dx1 > 1/MAXTAN){
                    if(!checkExist(approx,right_squares,MAXRANGE)){
                        if(right_squares.size()>BLOCKSIZE-1){
                            right_squares.clear();
                        }
                        right_squares.push_back(approx);
                    }
                }
                else if(dy1/dx1 > -MAXTAN && dy1/dx1 < -1/MAXTAN){
                    if(!checkExist(approx,front_squares,MAXRANGE)){
                        if(front_squares.size()>BLOCKSIZE-1){
                            front_squares.clear();
                        }
                        front_squares.push_back(approx);
                    }
                }
                else{
                    if(!checkExist(approx,down_squares,MAXRANGE)){
                        if(down_squares.size()>BLOCKSIZE-1){
                            down_squares.clear();
                        }
                        down_squares.push_back(approx);
                    }
                }
            }
            else{
                if(dy2/dx2 < MAXTAN  && dy2/dx2 > 1/MAXTAN){
                    if(!checkExist(approx,front_squares,MAXRANGE)){
                        if(front_squares.size()>BLOCKSIZE-1){
                            front_squares.clear();
                        }
                        front_squares.push_back(approx);
                    }
                }
                else if(dy2/dx2 > -MAXTAN && dy2/dx2 < -1/MAXTAN){
                    if(!checkExist(approx,right_squares,MAXRANGE)){
                        if(right_squares.size()>BLOCKSIZE-1){
                            right_squares.clear();
                        }
                        right_squares.push_back(approx);
                    }
                }
                else{
                    if(!checkExist(approx,down_squares,MAXRANGE)){
                        if(down_squares.size()>BLOCKSIZE-1){
                            down_squares.clear();
                        }
                        down_squares.push_back(approx);
                    }
                }
            }
        }
    }
}

bool checkExist(vector<Point>& square, vector<vector<Point> >& exist_squares,int maxRange){
    float core_x=0,core_y=0,tmp_core_x=0,tmp_core_y=0;

    // calculate the position of the input square's core
    float X1=square[0].x;
    float X2=square[1].x;
    float X3=square[2].x;
    float X4=square[3].x;
    float Y1=square[0].y;
    float Y2=square[1].y;
    float Y3=square[2].y;
    float Y4=square[3].y;
    core_x=((X3-X1)*(X4-X2)*(Y2-Y1)+X1*(Y3-Y1)*(X4-X2)-X2*(Y4-Y2)*(X3-X1))/
        ((Y3-Y1)*(X4-X2)-(Y4-Y2)*(X3-X1));
    core_y=(Y3-Y1)*((X4-X2)*(Y2-Y1)+(X1-X2)*(Y4-Y2))/
        ((Y3-Y1)*(X4-X2)-(Y4-Y2)*(X3-X1))+Y1;

    // calculate positions of all existing squares' cores
    // and compare the difference between their cores
    // if the difference is big enough, consider them as
    // different squares
    for(int i=0;i<exist_squares.size();i++){
        float x1=exist_squares[i][0].x;
        float x2=exist_squares[i][1].x;
        float x3=exist_squares[i][2].x;
        float x4=exist_squares[i][3].x;
        float y1=exist_squares[i][0].y;
        float y2=exist_squares[i][1].y;
        float y3=exist_squares[i][2].y;
        float y4=exist_squares[i][3].y;
        tmp_core_x=((x3-x1)*(x4-x2)*(y2-y1)+x1*(y3-y1)*(x4-x2)-x2*(y4-y2)*(x3-x1))/
            ((y3-y1)*(x4-x2)-(y4-y2)*(x3-x1));
        tmp_core_y=(y3-y1)*((x4-x2)*(y2-y1)+(x1-x2)*(y4-y2))/
            ((y3-y1)*(x4-x2)-(y4-y2)*(x3-x1))+y1;
        double distance = pow(core_x-tmp_core_x,2)+pow(core_y-tmp_core_y,2);
        //printf("%lf\n",distance);
        if( distance < maxRange){
            return true;
        }
    }
    return false;
}