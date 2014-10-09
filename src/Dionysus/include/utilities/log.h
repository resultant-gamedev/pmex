#ifndef __LOG_H__
#define __LOG_H__

#if _WIN32
#include <io.h>
#define STDERR_FILENO 2
#define STDOUT_FILENO 1
#define STDIN_FILENO 0
#else
#include <unistd.h>
#endif

#if LOGGING

#define RLOG_COMPONENT dionysus

#include <rlog/rlog.h>
#include <rlog/RLogChannel.h>
#include <rlog/StdioNode.h>
#include <sstream>

#undef RLOG_SECTION
#define RLOG_SECTION

template<class T>
std::string tostring(const T& t) { std::ostringstream out; out << t; return out.str(); }
template<class T>
std::string intostring(const T& t) { std::ostringstream out; t.operator<<(out); return out.str(); }

#define AssertMsg(cond, message, ...)		do { if (!(cond)) { rError(message, ##__VA_ARGS__); rAssertSilent(cond); } } while (0)
	
#else // LOGGING

#define rDebug(...)
#define rInfo(...)
#define rWarning(...)
#define rError(...)
#define rLog(...)

#define rAssert(...)
#define rAssertSilent(...)

#define DEF_CHANNEL(...) 0
#define RLOG_CHANNEL(...) 0

#define AssertMsg(cond, ...)

// To avoid undefined errors for RLogChannel, we create a dummy namespace
namespace rlog
{
	typedef		void			RLogChannel;

	class StdioNode
	{
		public:
								StdioNode(int,int)					{}
			void				subscribeTo(RLogChannel*)			{}

			static const int 	OutputColor = 0;
			static const int	OutputChannel = 0;
	};
}

#endif // LOGGING

static rlog::StdioNode stdoutLog(STDOUT_FILENO,
								 rlog::StdioNode::OutputColor + 
								 rlog::StdioNode::OutputChannel);

static rlog::StdioNode stderrLog(STDERR_FILENO,
								 rlog::StdioNode::OutputColor + 
								 rlog::StdioNode::OutputChannel);


#endif //__LOG_H__