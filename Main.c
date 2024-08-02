#define _ALLOW_RTCc_IN_STL
#include <stdio.h>
#include <stdlib.h>

//MSVC doesn't support <threads.h>
#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>
#define _sleep(duration) Sleep((DWORD)((duration) * 1000))

#include <time.h>
#include <stdbool.h>
#define AUTHOR "Jacob Manaker"

static void wait(double len)
{
#ifdef BE_EVIL_AND_POLL
	auto const &endwait = std::clock() + len * CLK_TCK;
	while(std::clock() < endwait) {}
#else
	_sleep(len);
#endif
}

_cdecl main()
{
	char const display[]="                                                                             Computers rock my world!\n";
	char const *const stop = display + sizeof(display) - 2;
	while (true)
		for (char const *index = display; index < stop; ++index)
		{
			printf(index);
			wait(.1);
			system("cls");
		}
}