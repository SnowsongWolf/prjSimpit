/*
 * simpit.h
 *
 *  Created on: Jan 10, 2021
 *      Author: Snow
 */



#ifdef ADD_EXPORTS
	#define ADDAPI __declspec(dllexport)
#else
	#define ADDAPI __declspec(dllimport)
#endif

#define ADDCALL __cdecl

#ifdef __cplusplus
extern "C"
{
#endif

ADDAPI int ADDCALL _hello();

#ifdef __cplusplus
}
#endif


