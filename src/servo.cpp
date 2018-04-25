#include "../include/servo.h"

using namespace std;

int servo_data[6][5]={
    11,   480,    970,    1490,   1980,
    8,   500,    975,    1500,   2030,
    6,   490,    960,    1480,   2030,
    12,   560,   1030,    1580,   2100,
    15,   570,   1040,    1560,   2030,
    3,   480,    910,    1470,   2070
};

void get_servo_sequence(int servo_stat[6],vector<array<int,2> >& servo_seq){
    for(int i=0;i<servo_seq.size();i++){
        int servo_id=servo_seq.at(i)[0];
        servo_stat[servo_id]+=servo_seq.at(i)[1];
        servo_seq.at(i)[1]=servo_data[servo_id][(servo_stat[servo_id]%360)/90+1];
        servo_seq.at(i)[0]=servo_data[servo_id][0];
    }
}

void servo_run(vector<array<int,2> >& servo_seq){


}
