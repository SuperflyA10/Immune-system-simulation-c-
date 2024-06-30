#ifndef AISSPACE_H
#define AISSPACE_H

#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <cstdlib>

using namespace std;

namespace AISSpace
{
    //Error constants
    const int ERR_ARG = -1;
    const int ERR_CONV = -2;

    //peices on the board
    const char blank = '.';
    const char detectors = '0';
    const char pathogen = 's';
    const int stimulation_threshold = 3;
    const int N = 5;

    int string_to_integer(string str);
    int gen_rand(int low,int high);

    typedef char* OneD_Array;
    typedef char** TwoD_Array;

    TwoD_Array alloc2D(int r, int c);
    void dealloc(TwoD_Array arr, int row);
    void init_Array(TwoD_Array &arr, int row,int col,int num_det);
    void Display(TwoD_Array &arr, int row,int col);
    void Place_dectectors(TwoD_Array &arr, int row,int col,char peice,int num);
    void Place_pathogen(TwoD_Array &arr, int row, int col,int &RowP,int &ColP);
    void Pause();

    void Run_sim(TwoD_Array arr, int row, int col, int &RowP, int &ColP);
    void clone_dectectors(TwoD_Array &arr, int row,int col,int R,int C);


}

#endif // AISSPACE_H
