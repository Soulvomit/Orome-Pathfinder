#pragma once
#include <iostream>
#include <string>
#include "../opf_native_win_wrapper/opf_native_interface_threaded.h"
#include "../opf_native_win_wrapper/opf_native_interface.h"

#pragma comment(lib, "opf_native_win_wrapper")

#define WIDTH 3000
#define HEIGHT 3000
#define MAX_PATHLENGTH 6000
#define PASSES 50
#define ACTIVETHREADS 4
#define BASECOST 1
#define FREQUENCY 5

void ProfileNonThreaded(const int width, const int height, const int max_pathlength, const int passes,
	const unsigned char frequency);

void ProfileThreaded(const int width, const int height, const int max_pathlength, const int passes,
	const int activethreads, const unsigned char frequency);

void Profile();