// pf_native_test.cpp : Defines the entry point for the console application.
#include "opf_native_test.h"

int main(int argc, char* argv[])
{
	if (argc == 8)
	{
		const int width = std::stoi(argv[1]);
		const int height = std::stoi(argv[2]);
		const int max_pathlength = std::stoi(argv[3]);
		const int passes = std::stoi(argv[4]);
		const int activethreads = std::stoi(argv[5]);
		const unsigned char frequency = (const unsigned char)std::stoi(argv[6]);
		const bool threaded = (const bool)std::stoi(argv[7]);

		std::cout << "Paramaterized benchmark started..." << std::endl << std::endl;

		if (threaded)
		{
			ProfileThreaded(width, height, max_pathlength, passes, activethreads, frequency);
			ProfileThreadedFailsafe(width, height, max_pathlength, passes, activethreads, frequency);
		}
		else
		{
			ProfileNonThreaded(width, height, max_pathlength, passes, frequency);
			ProfileNonThreadedFailsafe(width, height, max_pathlength, passes, frequency);
		}
		std::cout << "Benchmark done..." << std::endl;

		std::cin.get();
	}
	else
	{
		Profile();
	}
}

void ProfileNonThreaded(const int width, const int height, const int max_pathlength, const int passes, const unsigned char frequency)
{
	const int nStart[2] = { 0, 0 };
	const int nTarget[2] = { width - 1, height - 1 };
	const int nMapSize[2] = { width, height };

	double OutTime = 0;

	int failures = FindPathExProfiling(nStart[0], nStart[1], nTarget[0], nTarget[1], nMapSize[0], nMapSize[1],
		max_pathlength, OutTime, passes, true, BASECOST, true, frequency, false);

	std::cout << "Non-Threaded x86-64 Benchmark:" << std::endl;
	std::cout << "Time in MS: " << OutTime << std::endl;
	std::cout << "Failures: " << failures << "/" << passes << std::endl << std::endl;
}

void ProfileNonThreadedFailsafe(const int width, const int height, const int max_pathlength, const int passes, const unsigned char frequency)
{
	const int nStart[2] = { 0, 0 };
	const int nTarget[2] = { width - 1, height - 1 };
	const int nMapSize[2] = { width, height };

	double OutTime = 0;

	int failures = FindPathExProfiling(nStart[0], nStart[1], nTarget[0], nTarget[1], nMapSize[0], nMapSize[1],
		max_pathlength, OutTime, passes, true, BASECOST, true, frequency, true);

	std::cout << "Non-Threaded MSVC++ Benchmark:" << std::endl;
	std::cout << "Time in MS: " << OutTime << std::endl;
	std::cout << "Failures: " << failures << "/" << passes << std::endl << std::endl;
}


void ProfileThreaded(const int width, const int height, const int max_pathlength, const int passes, const int activethreads, 
	const unsigned char frequency)
{
	const int nStart[2] = { 0, 0 };
	const int nTarget[2] = { width - 1, height - 1 };
	const int nMapSize[2] = { width, height };

	double OutTime = 0;

	int failures = FindPathExProfilingThreaded(nStart[0], nStart[1], nTarget[0], nTarget[1], nMapSize[0], nMapSize[1],
		max_pathlength, OutTime, passes, activethreads, true, BASECOST, true, frequency, false);

	std::cout << "Threaded x86-64 Benchmark:" << std::endl;
	std::cout << "Time in MS: " << OutTime << std::endl;
	std::cout << "Failures: " << failures << "/" << passes << std::endl << std::endl;
}

void ProfileThreadedFailsafe(const int width, const int height, const int max_pathlength, const int passes, const int activethreads,
	const unsigned char frequency)
{
	const int nStart[2] = { 0, 0 };
	const int nTarget[2] = { width - 1, height - 1 };
	const int nMapSize[2] = { width, height };

	double OutTime = 0;

	int failures = FindPathExProfilingThreaded(nStart[0], nStart[1], nTarget[0], nTarget[1], nMapSize[0], nMapSize[1],
		max_pathlength, OutTime, passes, activethreads, true, BASECOST, true, frequency, true);

	std::cout << "Threaded MSVC++ Benchmark:" << std::endl;
	std::cout << "Time in MS: " << OutTime << std::endl;
	std::cout << "Failures: " << failures << "/" << passes << std::endl << std::endl;
}

void Profile()
{
	const int nStart[2] = { 0, 0 };
	const int nTarget[2] = { WIDTH - 1, HEIGHT - 1 };
	const int nMapSize[2] = { WIDTH, HEIGHT };
	double OutTime;

	std::cout << "Benchmark started..." << std::endl << std::endl;

	//int failures = FindPathExProfilingThreaded(nStart[0], nStart[1], nTarget[0], nTarget[1], nMapSize[0],
	//	nMapSize[1], MAX_PATHLENGTH, OutTime, PASSES, ACTIVETHREADS, true, BASECOST, true, FREQUENCY, false);
	//std::cout << "Threaded x86-64 Benchmark:" << std::endl;
	//std::cout << "Time in MS: " << OutTime << std::endl;
	//std::cout << "Failures: " << failures << "/" << PASSES << std::endl << std::endl;

	//int failures1 = FindPathExProfiling(nStart[0], nStart[1], nTarget[0], nTarget[1], nMapSize[0],
	//	nMapSize[1], MAX_PATHLENGTH, OutTime, PASSES, true, BASECOST, true, FREQUENCY, false);
	//std::cout << "Non-Threaded x86-64 Benchmark:" << std::endl;
	//std::cout << "Time in MS: " << OutTime << std::endl;
	//std::cout << "Failures: " << failures1 << "/" << PASSES << std::endl << std::endl;

	int failures2 = FindPathExProfilingThreaded(nStart[0], nStart[1], nTarget[0], nTarget[1], nMapSize[0],
		nMapSize[1], MAX_PATHLENGTH, OutTime, PASSES, ACTIVETHREADS, true, BASECOST, true, FREQUENCY, true);
	std::cout << "Threaded MSVC++ Benchmark:" << std::endl;
	std::cout << "Time in MS: " << OutTime << std::endl;
	std::cout << "Failures: " << failures2 << "/" << PASSES << std::endl << std::endl;

	int failures3 = FindPathExProfiling(nStart[0], nStart[1], nTarget[0], nTarget[1], nMapSize[0],
		nMapSize[1], MAX_PATHLENGTH, OutTime, PASSES, true, BASECOST, true, FREQUENCY, true);
	std::cout << "Non-Threaded MSVC++ Benchmark:" << std::endl;
	std::cout << "Time in MS: " << OutTime << std::endl;
	std::cout << "Failures: " << failures3 << "/" << PASSES << std::endl << std::endl;
	
	std::cout << "Benchmark done..." << std::endl;

	std::cin.get();
}