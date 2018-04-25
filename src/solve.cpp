#include <zconf.h>
#include <fcntl.h>
#include "../include/cube_data.h"
#include "../include/file_resolution.h"
#include "../include/servo.h"

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

int main(){
    //videoProcess(1);
    //videoProcess(2);
    //TODO add another camera data and combine the two frame data together
    string solve_input,solve_output;
    solve_input=read_file(sequence_path);
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
    //remove(sequence_path.c_str());
    cout << "\n------servo sequence------\n" << endl;
    print_servo(servo);
    cout << "\n------sequence result------\n" << endl;
    int servo_stat[6]={0};
    get_servo_sequence(servo_stat,servo);
    print_servo(servo);

    return 0;
}