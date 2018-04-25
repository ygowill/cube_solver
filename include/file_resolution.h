#ifndef CUBE_SOLVER_FILE_RESOLUTION
#define CUBE_SOLVER_FILE_RESOLUTION

#include <iostream>
#include <fstream>
#include "../include/cube_data.h"

bool in_table(char input,std::vector<char> table);
char get_usful_CH(FILE* fd);
void give_back_sequence(const char* filepath,std::vector<std::array<int,2> >& servo);
void print_servo(std::vector<std::array<int,2> > servo);
void store_result(const char* file_path,std::array<char, BLOCKSIZE>& stickers);
std::string read_file(const std::string file_path);

#endif //CUBE_SOLVER_FILE_RESOLUTION
