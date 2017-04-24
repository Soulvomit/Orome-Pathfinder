#pragma once
#include <iostream>
#include <string>
#include <opf_native_interface_threaded.h>
#include <opf_native_interface.h>

#pragma comment(lib, "opf_native_win_wrapper")

#define WIDTH 1000
#define HEIGHT 1000
#define MAX_PATHLENGTH 1500
#define PASSES 100
#define ACTIVETHREADS 4
#define FREQUENCY 6

void ProfileNonThreaded(const int width, const int height, const int max_pathlength, const int passes,
	const unsigned char frequency);

void ProfileNonThreadedFailsafe(const int width, const int height, const int max_pathlength, const int passes, 
	const unsigned char frequency);

void ProfileThreaded(const int width, const int height, const int max_pathlength, const int passes,
	const int activethreads, const unsigned char frequency);

void ProfileNonThreadedFailsafe(const int width, const int height, const int max_pathlength, const int passes,
	const unsigned char frequency);

void ProfileThreadedFailsafe(const int width, const int height, const int max_pathlength, const int passes,
	const int activethreads, const unsigned char frequency);

void Profile();