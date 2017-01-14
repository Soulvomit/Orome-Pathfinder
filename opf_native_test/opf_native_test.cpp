// pf_native_test.cpp : Defines the entry point for the console application.
#include "opf_native_test.h"

int main(int argc, char* argv[])
{
	if (argc == 7)
	{
		const int width = std::stoi(argv[1]);
		const int height = std::stoi(argv[2]);
		const int max_pathlength = std::stoi(argv[3]);
		const int passes = std::stoi(argv[4]);
		const int activethreads = std::stoi(argv[5]);
		const unsigned char frequency = (const unsigned char)std::stoi(argv[5]);

		std::cout << "Paramaterized benchmark started..." << std::endl << std::endl;

		ProfileThreaded(width, height, max_pathlength, passes, activethreads, frequency);

		ProfileNonThreaded(width, height, max_pathlength, passes, frequency);
		
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
		max_pathlength, OutTime, passes, true, BASECOST, true, frequency);

	std::cout << "Non-Threaded Benchmark:" << std::endl;
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
		max_pathlength, OutTime, passes, activethreads, true, BASECOST, true, frequency);

	std::cout << "Threaded Benchmark:" << std::endl;
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

	int failures = FindPathExProfilingThreaded(nStart[0], nStart[1], nTarget[0], nTarget[1], nMapSize[0],
		nMapSize[1], MAX_PATHLENGTH, OutTime, PASSES, ACTIVETHREADS, true, BASECOST, true, FREQUENCY);

	std::cout << "Threaded Benchmark:" << std::endl;
	std::cout << "Time in MS: " << OutTime << std::endl;
	std::cout << "Failures: " << failures << "/" << PASSES << std::endl << std::endl;

	int failures1 = FindPathExProfiling(nStart[0], nStart[1], nTarget[0], nTarget[1], nMapSize[0],
		nMapSize[1], MAX_PATHLENGTH, OutTime, PASSES, true, BASECOST, true, FREQUENCY);

	std::cout << "Non-Threaded Benchmark:" << std::endl;
	std::cout << "Time in MS: " << OutTime << std::endl;
	std::cout << "Failures: " << failures1 << "/" << PASSES << std::endl << std::endl;

	std::cout << "Benchmark done..." << std::endl;

	std::cin.get();
}