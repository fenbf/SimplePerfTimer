#include <iostream>

#include "SimplePerfTimer.h"

void internalCall()
{
	SIMPLEPERF_FUNCSTART;

	//::Sleep(1);
}

void longFunction()
{
	SIMPLEPERF_FUNCSTART;

	SIMPLEPERF_START("loop ");
	for (int i = 0; i < 10; ++i)
	{
		SIMPLEPERF_SCOPED("inside loop ");
		//::Sleep(10);
		internalCall();
	}
	SIMPLEPERF_END;
}

void shortMethod()
{
	SIMPLEPERF_FUNCSTART;

	SIMPLEPERF_START("loop ");
	for (int i = 0; i < 10; ++i);
		::Sleep(10);
	SIMPLEPERF_END;
}

int main()
{
	SIMPLEPERF_FUNCSTART;

	longFunction();
	shortMethod();

	SIMPLEPERF_REPORTALL_ATEXIT;

	return 0;
}
