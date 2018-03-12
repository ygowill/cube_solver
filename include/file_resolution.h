#ifndef CUBE_SOLVER_FILE_RESOLUTION
#define CUBE_SOLVER_FILE_RESOLUTION

#include <iostream>
#include <fstream>

bool in_table(char input,std::vector<char> table);
char get_usful_CH(FILE* fd);
void give_back_sequence(const char* filepath,std::vector<std::array<int,2> >& servo);
void print_servo(std::vector<std::array<int,2> > servo);

#endif //CUBE_SOLVER_FILE_RESOLUTION
