/***************************************************************************

  Author: Michael Stumpfl

  Date:   2019-07-15

  API:    C

  Libraries:
    ---

  Functionality:
    ASCII/MBCS variant of the CRT's "winput_l()" function to parse
    formatted strings.

  Known Bugs:
    ---

****************************************************************************/
#undef _UNICODE

/* crt\src\crtdefs.h:743 */
#define __UPDATE_LOCALE(ptd, ptloci)  if( ( (ptloci) != __ptlocinfo) &&      \
                                          !( (ptd)->_ownlocale & __globallocalestatus)) \
                                      {                                     \
                                          (ptloci) = __updatetlocinfo();    \
                                      }

#define __UPDATE_MBCP(ptd, ptmbci)  if( ( (ptmbci) != __ptmbcinfo) &&      \
                                          !( (ptd)->_ownlocale & __globallocalestatus)) \
                                      {                                     \
                                          (ptmbci) = __updatetmbcinfo();    \
                                      }

/* crt\src\setlocal.h:180 */
/*
#ifndef _THREADMBCINFO
typedef struct threadmbcinfostruct {
        int refcount;
        int mbcodepage;
        int ismbcodepage;
        int mblcid;
        unsigned short mbulinfo[6];
        unsigned char mbctype[257];
        unsigned char mbcasemap[256];
} threadmbcinfo;
#define _THREADMBCINFO
#endif
*/

/* crt\src\crtdefs.h:2152 */
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct * pthreadlocinfo;
typedef struct threadmbcinfostruct * pthreadmbcinfo;

#ifdef __cplusplus
extern "C" {
#endif

/* crt\src\ctype.h:92 */
extern pthreadmbcinfo __ptmbcinfo;
extern int __globallocalestatus;

pthreadlocinfo __cdecl __updatetlocinfo(void);
pthreadmbcinfo __cdecl __updatetmbcinfo(void);

#pragma warning (push)
#pragma warning (disable : 4127)  /* input.c(528) : warning C4127: conditional expression is constant */
#pragma warning (disable : 4201)  /* src\crt\fltintrn.h(92) : warning C4201: nonstandard extension used : nameless struct/union */
#pragma warning (disable : 4244)  /* input.c(1022) : warning C4244: 'argument' : conversion from '_TINT' to '_TCHAR', possible loss of data */
#pragma warning (disable : 4701)  /* input.c(1021) : warning C4701: potentially uninitialized local variable 'num64' used */

#ifndef _UNICODE
  #ifdef _SAFECRT_IMPL
  #define __tinput        crt_input
  #define __tinput_s      crt_input_s
  #else  /* _SAFECRT_IMPL */
  #define _tinput_l      crt_input_l
  #define _tinput_s_l    crt_input_s_l
  #endif  /* _SAFECRT_IMPL */
#endif

#include "crt\input.c"

#pragma warning (pop)

#ifdef BUILDING_INPUT_L
#include "msvcrt_missing.c"
#endif

#ifdef __cplusplus
}
#endif
