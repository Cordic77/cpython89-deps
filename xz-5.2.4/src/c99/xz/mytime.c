///////////////////////////////////////////////////////////////////////////////
//
/// \file       mytime.c
/// \brief      Time handling functions
//
//  Author:     Lasse Collin
//
//  This file has been put into the public domain.
//  You can do whatever you want with this file.
//
///////////////////////////////////////////////////////////////////////////////

#include "private.h"

#if !(defined(HAVE_CLOCK_GETTIME) && HAVE_DECL_CLOCK_MONOTONIC)
#ifndef _WIN32
#	include <sys/time.h>
#else
// http://stackoverflow.com/questions/10905892/equivalent-of-gettimeday-for-windows
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdint.h> // portable: uint64_t   MSVC: __int64 

// MSVC defines this in winsock2.h!?
typedef struct timeval {
  long tv_sec;
  long tv_usec;
} timeval;

int gettimeofday (struct timeval * tp, struct timezone * tzp)
{
  // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
  static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

  SYSTEMTIME  system_time;
  FILETIME    file_time;
  uint64_t    time;

  GetSystemTime (&system_time);
  SystemTimeToFileTime (&system_time, &file_time);
  time = ((uint64_t)file_time.dwLowDateTime);
  time += ((uint64_t)file_time.dwHighDateTime) << 32;

  tp->tv_sec = (long)((time - EPOCH) / 10000000L);
  tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
  return 0;
}
#endif
#endif

uint64_t opt_flush_timeout = 0;
bool flush_needed;

static uint64_t start_time;
static uint64_t next_flush;


/// \brief      Get the current time as milliseconds
///
/// It's relative to some point but not necessarily to the UNIX Epoch.
static uint64_t
mytime_now(void)
{
	// NOTE: HAVE_DECL_CLOCK_MONOTONIC is always defined to 0 or 1.
#if defined(HAVE_CLOCK_GETTIME) && HAVE_DECL_CLOCK_MONOTONIC
	// If CLOCK_MONOTONIC was available at compile time but for some
	// reason isn't at runtime, fallback to CLOCK_REALTIME which
	// according to POSIX is mandatory for all implementations.
	static clockid_t clk_id = CLOCK_MONOTONIC;
	struct timespec tv;
	while (clock_gettime(clk_id, &tv))
		clk_id = CLOCK_REALTIME;

	return (uint64_t)(tv.tv_sec) * UINT64_C(1000) + tv.tv_nsec / 1000000;
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (uint64_t)(tv.tv_sec) * UINT64_C(1000) + tv.tv_usec / 1000;
#endif
}


extern void
mytime_set_start_time(void)
{
	start_time = mytime_now();
	next_flush = start_time + opt_flush_timeout;
	flush_needed = false;
	return;
}


extern uint64_t
mytime_get_elapsed(void)
{
	return mytime_now() - start_time;
}


extern void
mytime_set_flush_time(void)
{
	next_flush = mytime_now() + opt_flush_timeout;
	flush_needed = false;
	return;
}


extern int
mytime_get_flush_timeout(void)
{
	if (opt_flush_timeout == 0 || opt_mode != MODE_COMPRESS)
		return -1;

	const uint64_t now = mytime_now();
	if (now >= next_flush)
		return 0;

	const uint64_t remaining = next_flush - now;
	return remaining > INT_MAX ? INT_MAX : (int)remaining;
}
