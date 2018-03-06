#include "color_operation.h"

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

void cube_color_reduce(cv::Mat& src, cv::Mat& dst){

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
