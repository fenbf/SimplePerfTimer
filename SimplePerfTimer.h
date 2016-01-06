#ifndef SIMPLEPERFTIMER_H
#define SIMPLEPERFTIMER_H

#define ENABLE_SIMPLEPERF
#define SIMPLEPERF_SHOWIMMEDIATE false

#ifdef ENABLE_SIMPLEPERF

// in a larger project this should go into a precompiled header...
#include <windows.h>
#include <string>
#include <vector>
#include <tuple>

#define PERF_PRINTF_FUNC printf

class SimplePerfTimer
{
public:
	SimplePerfTimer(const char* strText, bool bShowImmediate);
	~SimplePerfTimer();

	SimplePerfTimer(const SimplePerfTimer&) = delete;
	SimplePerfTimer& operator=(const SimplePerfTimer&) = delete;

	static void ReportAll();

private:
	unsigned m_id;
	const char *m_str;
	const bool m_bShowImmediate;
	LARGE_INTEGER m_start;

	static std::vector<std::tuple<std::string, double, int>> s_data;
	static LARGE_INTEGER s_freq;
	static int s_indent;
};

#define SIMPLEPERF_FUNCSTART SimplePerfTimer __xperfstart##__COUNTER__(__FUNCTION__" : %f\n", SIMPLEPERF_SHOWIMMEDIATE)
#define SIMPLEPERF_SCOPED(str) SimplePerfTimer __xperfstart##__COUNTER__(str" : %f\n", SIMPLEPERF_SHOWIMMEDIATE)
#define SIMPLEPERF_START(str) { SimplePerfTimer __xperfstart##__COUNTER__(str" : %f\n", SIMPLEPERF_SHOWIMMEDIATE)
#define SIMPLEPERF_END }
#define SIMPLEPERF_REPORTALL SimplePerfTimer::ReportAll
#define SIMPLEPERF_REPORTALL_ATEXIT atexit(SimplePerfTimer::ReportAll);

#else

#define SIMPLEPERF_FUNCSTART
#define SIMPLEPERF_SCOPED
#define SIMPLEPERF_START
#define SIMPLEPERF_END
#define SIMPLEPERF_REPORTALL
#define SIMPLEPERF_REPORTALL_ATEXIT

#endif // ENABLE_SIMPLEPERF

#endif // SIMPLEPERFTIMER_H
