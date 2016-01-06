#include "SimplePerfTimer.h"

#ifdef ENABLE_SIMPLEPERF

std::vector<std::tuple<std::string, double, int>> SimplePerfTimer::s_data;
LARGE_INTEGER SimplePerfTimer::s_freq = { 0, 0 };
int SimplePerfTimer::s_indent = 0;

SimplePerfTimer::SimplePerfTimer(const char* strText, bool bShowImmediate) : m_str(strText), m_bShowImmediate(bShowImmediate)
{
	if (s_freq.QuadPart == 0)
		QueryPerformanceFrequency(&s_freq);

	QueryPerformanceCounter(&m_start);

	if (!m_bShowImmediate)
	{
		m_id = s_data.size();
		s_data.push_back(std::make_tuple(m_str, 0.0, s_indent));
		s_indent++;
	}
}

SimplePerfTimer::~SimplePerfTimer()
{
	LARGE_INTEGER endTime, tDelta;
	QueryPerformanceCounter(&endTime);

	tDelta.QuadPart = endTime.QuadPart - m_start.QuadPart;
	tDelta.QuadPart *= 1000000;
	tDelta.QuadPart /= s_freq.QuadPart;

	const double doubleElapsed = (double)tDelta.QuadPart / 1000.0;
	if (m_bShowImmediate)
	{
		PERF_PRINTF_FUNC(m_str, doubleElapsed);	// will show output in milliseconds
	}
	else
	{
		std::get<1>(s_data[m_id]) = doubleElapsed;
	}

	--s_indent;
}

void SimplePerfTimer::ReportAll()
{
	for (const auto &d : s_data)
	{
		int indents = std::get<2>(d);
		while (indents-- > 0) PERF_PRINTF_FUNC("  ");
		PERF_PRINTF_FUNC(std::get<0>(d).c_str(), std::get<1>(d));
	}
}

#endif // ENABLE_SIMPLEPERF
