#ifndef _RPCH_H_
#define _RPCH_H_

#include <windows.h>

#undef __rpch_ovr
#if defined (__GNUC__)
#define __rpch_ovr static __attribute__ ((__unused__)) __inline__ __cdecl
#elif defined(__cplusplus)
#define __rpch_ovr inline __cdecl
#else
#define __rpch_ovr static __cdecl
#endif

#undef RPCH__
#define RPCH__(_FUNC_)	rpch_##_FUNC_

#endif /* _RPCH_H_ */
