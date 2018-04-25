#ifndef CUBE_SOLVER_SERVO_H
#define CUBE_SOLVER_SERVO_H

#include <iostream>
#include <vector>
#include <array>

void get_servo_sequence(int servo_stat[6],std::vector<std::array<int,2> >& servo_seq);
void servo_run(std::vector<std::array<int,2> >& servo_seq);

#endif //CUBE_SOLVER_SERVO_H
