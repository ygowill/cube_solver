#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

const int MAXRANGE = 1000;
const int MAXTAN = 3;
const int PICSIZE = 200;
const int CUBESHAPE = 4;
const int FRAMESIZE_X = 1280;
const int FRAMESIZE_Y = 720;
const int BLOCKSIZE = CUBESHAPE*CUBESHAPE;
const int FRONT_DISTANCE_COMPENSATION_X = 6;
const int FRONT_DISTANCE_COMPENSATION_Y = 5;
const int FRONT_DISTANCE_COMPENSATION_XY_X = 30;
const int FRONT_DISTANCE_COMPENSATION_XY_Y = 0;
const int RIGHT_DISTANCE_COMPENSATION_X = 4;
const int RIGHT_DISTANCE_COMPENSATION_Y = 6;
const int RIGHT_DISTANCE_COMPENSATION_XY_X = -35;
const int RIGHT_DISTANCE_COMPENSATION_XY_Y = 20;
const int DOWN_DISTANCE_COMPENSATION_X = 4;
const int DOWN_DISTANCE_COMPENSATION_Y = 5;
const int DOWN_DISTANCE_COMPENSATION_XY_X = 5;
const int DOWN_DISTANCE_COMPENSATION_XY_Y = -25;

using namespace cv;
using namespace std;

vector<vector<Point> > front_squares;
array<Point2f,CUBESHAPE> front_corner;
vector<array<Point2f,CUBESHAPE> > f_corners;
vector<vector<Point> > down_squares;
array<Point2f,CUBESHAPE> down_corner;
vector<array<Point2f,CUBESHAPE> > d_corners;
vector<vector<Point> > right_squares;
array<Point2f,CUBESHAPE> right_corner;
vector<array<Point2f,CUBESHAPE> > r_corners;

/*void colorReduce(const Mat& src,Mat& dst,int K=64){
    int n = src.rows * src.cols;
    Mat data = src.reshape(1, n);
    data.convertTo(data, CV_32F);

    vector<int> labels;
    Mat1f colors;
    kmeans(data, K, labels, TermCriteria(), 1, KMEANS_PP_CENTERS, colors);
    for (int i = 0; i < n; ++i){
        data.at<float>(i, 0) = colors(labels[i], 0);
        data.at<float>(i, 1) = colors(labels[i], 1);
        data.at<float>(i, 2) = colors(labels[i], 2);
    }
    Mat reduced = data.reshape(3, src.rows);
    reduced.convertTo(dst, CV_8U);
}*/

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

void findFrontKeyBlock(vector<array<Point2f,CUBESHAPE> >& corners,int &core_square_index){
    Point2f down_right=corners[0][3];
    for(int i=0;i<corners.size();i++){
        double distance = pow(corners[i][3].x-FRAMESIZE_X,2)+pow(corners[i][3].y-FRAMESIZE_Y,2);
        if(distance < (pow(down_right.x-FRAMESIZE_X,2)+pow(down_right.y-FRAMESIZE_Y,2))){
            core_square_index=i;
            down_right = corners[i][3];
        }
    }
}

void findRightKeyBlock(vector<array<Point2f,CUBESHAPE> >& corners,int &core_square_index){
    Point2f down_lift=corners[0][0];
    for(int i=0;i<corners.size();i++){
        double distance = pow(corners[i][2].x,2)+pow(corners[i][2].y-FRAMESIZE_Y,2);
        if(distance < (pow(down_lift.x,2) + pow(down_lift.y-FRAMESIZE_Y,2))){
            core_square_index=i;
            down_lift = corners[i][2];
        }
    }
}

void findDownKeyBlock(vector<array<Point2f,CUBESHAPE> >& corners,int &core_square_index){
    Point2f top_right=corners[0][0];
    for(int i=0;i<corners.size();i++){
        if(corners[i][1].y < top_right.y){
            core_square_index=i;
            top_right = corners[i][1];
        }
    }
}

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

int main(){
    VideoCapture cap(1); // open webcam

    if (!cap.isOpened()){
        return -1;
    }

    Mat frame;
    Mat mean_frame;
    vector<vector<Point> > squares;

    waitKey(3000);
    cap >> mean_frame;
    time_t start,stop;
    start = time(NULL);
    while (true){
        cap >> frame;
        //frame = imread("/Users/qinkai/Desktop/cube.JPG");
        if (frame.empty()){
            return -1;
        }
        printf("detecting...\n");
        findSquares(frame, squares);
        /*drawSquares(frame, front_squares);
        drawSquares(frame, right_squares);
        drawSquares(frame, down_squares);*/
        printf("sum: %ld,front: %ld\n",squares.size(),front_squares.size());
        printf("sum: %ld,right: %ld\n",squares.size(),right_squares.size());
        printf("sum: %ld,down: %ld\n",squares.size(),down_squares.size());
        printf("finishing detcetion...\n");
        addWeighted(mean_frame,0.9,frame,0.1,0,mean_frame);

        stop = time(NULL);
        if(stop - start>3){
            break;
        }
        waitKey(1);
    }

    Point2f pts_dst[] = {
        Point(0,0),
        Point(PICSIZE,0),
        Point(0,PICSIZE) ,
        Point(PICSIZE,PICSIZE)
    };

    printf("cutting...\n");
    int f_index,r_index,d_index;
    findFrontCorner(front_squares,f_corners);
    findBound(f_corners,front_corner,3);
    findFrontKeyBlock(f_corners,f_index);
    findRightCorner(right_squares,r_corners);
    findBound(r_corners,right_corner,2);
    findRightKeyBlock(r_corners,r_index);
    findDownCorner(down_squares,d_corners);
    findBound(d_corners,down_corner,1);
    findDownKeyBlock(d_corners,d_index);

    /*for(int i=0;i<4;i++){
        //circle(frame,Point((int)f_corners[f_index][i].x,(int)f_corners[f_index][i].y),5,Scalar(0,0,0),3);
        //circle(frame,Point((int)r_corners[r_index][i].x,(int)r_corners[r_index][i].y),5,Scalar(0,0,0),3);
        //circle(frame,Point((int)d_corners[d_index][i].x,(int)d_corners[d_index][i].y),5,Scalar(0,0,0),3);
        circle(frame,Point((int)front_corner[i].x,(int)front_corner[i].y),5,Scalar(0,255,255),3);
        circle(frame,Point((int)right_corner[i].x,(int)right_corner[i].y),5,Scalar(0,255,255),3);
        circle(frame,Point((int)down_corner[i].x,(int)down_corner[i].y),5,Scalar(0,255,255),3);
        //printf("(%d,%d) ",(int)front_corner[i].x,(int)front_corner[i].y);
        //printf("(%d,%d) ",(int)f_corners[index][i].x,(int)f_corners[index][i].y);
    }*/
    imshow("Rubik's Detection -ygowill", frame);

    Mat front_m = getPerspectiveTransform(front_corner.data(),pts_dst);
    Mat front_image;
    warpPerspective(mean_frame,front_image,front_m,mean_frame.size());
    Mat roi_front = front_image(Rect(0,0,PICSIZE,PICSIZE));
    imshow("roi front",roi_front);
    Mat right_m = getPerspectiveTransform(right_corner.data(),pts_dst);
    Mat right_image;
    warpPerspective(mean_frame,right_image,right_m,mean_frame.size());
    Mat roi_right = right_image(Rect(0,0,PICSIZE,PICSIZE));
    imshow("roi right",roi_right);
    Mat down_m = getPerspectiveTransform(down_corner.data(),pts_dst);
    Mat down_image;
    warpPerspective(mean_frame,down_image,down_m,mean_frame.size());
    Mat roi_down = down_image(Rect(0,0,PICSIZE,PICSIZE));
    imshow("roi down",roi_down);
    printf("processing done...\n");
    waitKey(600000);

    //TODO color quantization and store
    //TODO add another camera data and build the whole cube
    //TODO cube solve algorithm

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

    return 0;
}