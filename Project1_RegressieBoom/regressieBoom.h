#pragma once
#include <string>

using namespace std;


void print_results(const double * results, const string * headers, const string * units, int rows, int cols);

void csv_write(ofstream & out_file, const double * data, const string * headers, int rows, int cols, char sep = ',');
