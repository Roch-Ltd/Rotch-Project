#ifndef _RGRAPHICS_H_
#define _RGRAPHICS_H_

#if defined(WIN32)

#include <windows.h>

static HANDLE std_console_handle;
void _init_graph()
{
	std_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void console_colour(int _clr_)
{
	SetConsoleTextAttribute(std_console_handle, _clr_);	
} 

#else
# error	Only Windows is supported now!
#endif

#endif /* _RGRAPHICS_H_ */
