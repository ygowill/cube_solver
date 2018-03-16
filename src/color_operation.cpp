#include "../include/color_operation.h"

using namespace cv;

void cube_color_reduce(cv::Mat& src, cv::Mat& dst){
    std::vector<Mat > channels;
    Mat hsv_img;
    cvtColor(src,hsv_img,COLOR_BGR2HSV);
    MatIterator_<Vec3b> colorit, colorend;
    for(colorit = hsv_img.begin<Vec3b>(), colorend = hsv_img.end<Vec3b>(); colorit != colorend; ++colorit){
        //detect color and set hue value
        if(((*colorit)[0]>=0 && (*colorit)[0]<=9) || ((*colorit)[0]>=151 && (*colorit)[0]<=180)){
            (*colorit)[0]=RED;
        }
        else if((*colorit)[0]>=10 && (*colorit)[0]<=24){
            (*colorit)[0]=ORANGE;
        }
        else if((*colorit)[0]>=25 && (*colorit)[0]<=45){
            (*colorit)[0]=YELLOW;
        }
        else if((*colorit)[0]>=46 && (*colorit)[0]<=100){
            (*colorit)[0]=GREEN;
        }
        else{
            (*colorit)[0]=BLUE;
        }

        //detect white and set the saturation value
        if(((*colorit)[1]>=0 && (*colorit)[1]<=10) && ((*colorit)[2]>=240 && (*colorit)[2]<=255)){
            (*colorit)[1]=WHITE_S;
        }
        else{
            (*colorit)[1]=255;
        }

        //set the brightness value
        //(*colorit)[2]=128;
    }
    cvtColor(hsv_img,dst,COLOR_HSV2BGR);

}

void my_kmeans(cv::Mat& src, cv::Mat& dst,int clusterCount,int attempts){
    //step 1 : map the src to the samples
    cv::Mat samples(src.total(), 3, CV_32F);
    auto samples_ptr = samples.ptr<float>(0);
    for( int row = 0; row != src.rows; ++row){
        auto src_begin = src.ptr<uchar>(row);
        auto src_end = src_begin + src.cols * src.channels();
        //auto samples_ptr = samples.ptr<float>(row * src.cols);
        while(src_begin != src_end){
            samples_ptr[0] = src_begin[0];
            samples_ptr[1] = src_begin[1];
            samples_ptr[2] = src_begin[2];
            samples_ptr += 3; src_begin +=3;
        }
    }

    //step 2 : apply kmeans to find labels and centers
    cv::Mat labels;
    cv::Mat centers;
    kmeans(samples, clusterCount, labels,
           cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS,
                            10, 0.01),
           attempts, cv::KMEANS_PP_CENTERS, centers);

    //step 3 : map the centers to the output
    cv::Mat new_image(src.size(), src.type());
    for( int row = 0; row != src.rows; ++row){
        auto new_image_begin = new_image.ptr<uchar>(row);
        auto new_image_end = new_image_begin + new_image.cols * 3;
        auto labels_ptr = labels.ptr<int>(row * src.cols);

        while(new_image_begin != new_image_end){
            int const cluster_idx = *labels_ptr;
            auto centers_ptr = centers.ptr<float>(cluster_idx);
            new_image_begin[0] = centers_ptr[0];
            new_image_begin[1] = centers_ptr[1];
            new_image_begin[2] = centers_ptr[2];
            new_image_begin += 3; ++labels_ptr;
        }
    }
    dst = new_image;
}

void get_cube_color(Mat& roi,std::array<char, BLOCKSIZE>& color){
    for(int i=0;i<CUBESHAPE;i++){
        for(int j=0;j<CUBESHAPE;j++){
            Mat tmp_roi=roi(Rect(j*STICKERSIZE,i*STICKERSIZE,STICKERSIZE,STICKERSIZE));
            color[i*CUBESHAPE+j]=get_block_color(tmp_roi);
            printf("%c  ",color[i*CUBESHAPE+j]);
        }
        printf("\n");
    }
}

char get_block_color(Mat& roi){
    //imshow("roi",roi);
    Mat src,channels[3],hist;
    cvtColor(roi,src,COLOR_BGR2HSV);
    split(src,channels);

    //calculate the s channel to decide if the domain color is white
    int sSize = 2;
    float sranges[] = { 0,255 };
    const float* psranges = sranges;
    calcHist(&channels[1], 1, 0, Mat(), hist, 1, &sSize, &psranges);
    normalize(hist, hist, 0, 255, NORM_MINMAX);
    //printf("********\n%d  %d\n********\n",saturate_cast<int>(hist.at<float>(0)),saturate_cast<int>(hist.at<float>(1)));
    if(saturate_cast<int>(hist.at<float>(0)) > saturate_cast<int>(hist.at<float>(1))){
        return 'W';
    }

    //calculate the h channel to decide the rest colors
    int hsize = 18;
    float hranges[] = { 0,180 };
    const float* phranges = hranges;
    calcHist(&channels[0], 1, 0, Mat(), hist, 1, &hsize, &phranges);
    normalize(hist, hist, 0, 255, NORM_MINMAX);

    int maxVal=saturate_cast<int>(hist.at<float>(0));
    int loc=0;
    for (int i = 1; i < hsize; i++){
        int val = saturate_cast<int>(hist.at<float>(i));
        if(val>maxVal){
            loc = i;
            maxVal = val;
        }
    }

    switch (loc){
        case 0:return 'R';
        case 1:return 'O';
        case 3:return 'Y';
        case 7:return 'G';
        case 12:return 'B';
        default: return 'W';
    }
}
