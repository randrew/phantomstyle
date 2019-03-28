#pragma once

#ifdef BUILD_WITH_EASY_PROFILER

// In Qt Creator, disable recursive macro expansion warnings for clang. We do
// this because the clang static analyzer runs in Qt Creator for code analysis
// even if we're using the MSVC compiler, and these profiler macros won't be
// analyzed correctly.
#ifdef _MSC_VER
#pragma warning(push)
// Disable unknown pragma warning in MSVC
#pragma warning(disable : 4068)
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-const-variable"

#pragma warning(pop)
#endif

#include <easy/profiler.h>

// Remove the unused-const-variable warning suppression
#ifdef _MSC_VER
#pragma warning(push)
// Disable unknown pragma warning in MSVC
#pragma warning(disable : 4068)
#pragma clang diagnostic pop
#pragma warning(pop)
#endif

#else // BUILD_WITH_EASY_PROFILER

// Our own wrappers to avoid including easy/profiler.h at all
#define EASY_BLOCK(...)
#define EASY_END_BLOCK
#define EASY_FUNCTION(...)
#define EASY_EVENT(...)
#define EASY_THREAD(...)

#endif // BUILD_WITH_EASY_PROFILER
