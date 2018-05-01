#include <zconf.h>
#include <fcntl.h>
#include <thread>
#include "../include/cube_data.h"
#include "../include/file_resolution.h"
#include "../include/servo.h"
#include "../include/video.h"

using namespace cv;
using namespace std;

int main(){
    Cube cube1,cube2;
    cube1.cameraID=1;
    cube2.cameraID=2;
    videoProcess(cube1);
    //thread t1(videoProcess,std::ref(cube1));
    //thread t2(videoProcess,std::ref(cube2));
    //t1.join();
    //t2.join();


    //TODO combine the two cube face color data together
    store_result(sequence_path.c_str(),cube1.d_stickers);
    store_result(sequence_path.c_str(),cube1.r_stickers);
    store_result(sequence_path.c_str(),cube1.f_stickers);
    store_result(sequence_path.c_str(),cube2.d_stickers);
    store_result(sequence_path.c_str(),cube2.r_stickers);
    store_result(sequence_path.c_str(),cube2.f_stickers);

    /*string solve_input,solve_output;
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

    servo_run(servo);*/

    return 0;
}