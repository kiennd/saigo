#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

 #include <print.hpp>

void print::help (string program_name)
{
	cout << "Usage: " << program_name << " [options] -i <INPUT> [-o <OUTPUT>]\n" <<
	"Return all text regions found in <INPUT> rounded by rectangles in <OUTPUT>.\n" <<
	"Options:\n\n"
	"\t-v <VALUE>\t\tMaximum Pixel variance that reports a text range.\n" << 
	"\t-l <VALUE>\t\tMaximum Distance between ranges that still reports unique area.\n" << 
	"\t-s <VALUE>\t\tMaximum Similarity Factor between pixels.\n" << 
	"\t-i <FILE>\t\tInput file.\n" <<
	"\t-o <FILE>\t\tOutput File. Default 'output_image.ppm'. \n" <<
	"\t-h\t\t\tShow this help.\n" ;
}

void print::error ( string program_name , string error_str )
{
	// Print errors messages in red.
	cerr << "\e[31;01m";
	cerr << program_name << ": " << error_str << endl;
	cerr << "\e[0m";

	// Print help and finish
	help(program_name);
	_exit(1);
}

void print::percent ( int val , int total)
{	
	int perc = (val*100)/total;

	// Erase the line to print to maintain 
	// just the current percentage on screen
	cout << "\r" << "[" << perc << "%]";
	cout.flush();	
}

