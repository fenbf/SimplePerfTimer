#ifndef SIMPLEPERFTIMER_H
#define SIMPLEPERFTIMER_H

#define ENABLE_SIMPLEPERF

#ifdef ENABLE_SIMPLEPERF

// in a larger project this should go into a precompiled header...
#include <windows.h>

#define PERF_PRINTF_FUNC printf

class SimplePerfTimer
{
public:
	SimplePerfTimer(const char* strText)
	{
		QueryPerformanceCounter(&m_start);
	}

	~SimplePerfTimer()
	{
		LARGE_INTEGER endTime, tDelta;
		QueryPerformanceCounter(&endTime);

		static LARGE_INTEGER s_freq = { 0, 0 };

		if (s_freq.QuadPart == 0)
			QueryPerformanceFrequency(&s_freq);

		tDelta.QuadPart = endTime.QuadPart - m_start.QuadPart;
		tDelta.QuadPart *= 1000000;
		tDelta.QuadPart /= s_freq.QuadPart;

		const double doubleElapsed = (double)tDelta.QuadPart / 1000.0;

		PERF_PRINTF_FUNC(m_str, doubleElapsed);	// will show output in milliseconds
	}

	SimplePerfTimer(const SimplePerfTimer&) = delete;
	SimplePerfTimer& operator=(const SimplePerfTimer&) = delete;

private:
	const char *m_str;
	LARGE_INTEGER m_start;
};

#define SIMPLEPERF_FUNCSTART SimplePerfTimer __xperfstart##__COUNTER__(__FUNCTION__" : %f\n")
#define SIMPLEPERF_SCOPED(str) SimplePerfTimer __xperfstart##__COUNTER__(str" : %f\n")
#define SIMPLEPERF_START(str) { SimplePerfTimer __xperfstart##__COUNTER__(str" : %f\n")
#define SIMPLEPERF_END }

#else

#define SIMPLEPERF_FUNCSTART
#define SIMPLEPERF_SCOPED
#define SIMPLEPERF_START
#define SIMPLEPERF_END

#endif // ENABLE_SIMPLEPERF

#endif // SIMPLEPERFTIMER_H
