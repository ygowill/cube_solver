#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

void colorReduce(const Mat& src,Mat& dst,int K=64){
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
}

static void drawSquares( Mat& image, const vector<vector<Point> >& squares ){
    for( size_t i = 0; i < squares.size(); i++ ){
        const Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        int shift = 1;

        Rect r=boundingRect( Mat(squares[i]));
        r.x = r.x + r.width / 4;
        r.y = r.y + r.height / 4;
        r.width = r.width / 2;
        r.height = r.height / 2;

        Mat roi = image(r);
        Scalar color = mean(roi);
        polylines(image, &p, &n, 1, true, color, 2, LINE_AA, shift);
    }
}

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
static void findSquares( const Mat& image, vector<vector<Point> >& squares , bool inv=false){
    squares.clear();
    Mat gray,gray0,color_gray,image_clone,reduced;
    vector<vector<Point> > contours;

    //use k-means to do color quantization
    /*cvtColor(image,image_clone,COLOR_BGR2HSV);
    colorReduce(image_clone,reduced,32);
    imshow("color reduce result",reduced);*/
    cvtColor(image,gray0,COLOR_BGR2GRAY);
    GaussianBlur(gray0, gray0, Size(11,11), 0, 0);
    //pyrMeanShiftFiltering(image,image,spatialRad,colorRad,maxPryLevel);
    //cvtColor(image,gray0,COLOR_BGR2GRAY);
    Canny(gray0,gray, 0, 30, 3);

    imshow("canny result",gray);

    // find contours and store them all as a list
    findContours(gray, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<Point> approx;

    // test each contour
    for( size_t i = 0; i < contours.size(); i++ ){
        // approximate contour with accuracy proportional
        // to the contour perimeter
        approxPolyDP(Mat(contours[i]), approx, 9, true);

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
        }
    }
}

int main(){
    VideoCapture cap(1); // open webcam

    if (!cap.isOpened()){
        return -1;
    }

    Mat frame;
    vector<vector<Point> > squares;

    while (true){
        cap >> frame;
        //frame = imread("/Users/qinkai/Desktop/cube.JPG");
        if (frame.empty()){
            return -1;
        }
        findSquares(frame, squares);
        drawSquares(frame, squares);
        imshow("Rubic Detection Demo", frame);
        waitKey(1);
    }
    return 0;
}