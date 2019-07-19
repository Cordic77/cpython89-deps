#ifndef M_FORMATTED_IO_H
#define M_FORMATTED_IO_H

#include <crtdefs.h>              /* wchar_t */
#include <stdarg.h>               /* va_list */

#ifndef _FILE_DEFINED
struct _iobuf {
        char *_ptr;
        int   _cnt;
        char *_base;
        int   _flag;
        int   _file;
        int   _charbuf;
        int   _bufsiz;
        char *_tmpfname;
        };
typedef struct _iobuf FILE;
#define _FILE_DEFINED
#endif

/* Function declarations: */
#ifdef __cplusplus
extern "C" {
#endif

/*===  [v]sprintf() variants  ===*/
int __cdecl c99_vsprintf (char *dst_buf, char const format [], va_list arglist);  /*CPython*/
int __cdecl c99_vsprintf_s (char *dst_buf, size_t size_in_bytes, char const format [], va_list arglist);
int __cdecl c99_vsnprintf (char *dst_buf, size_t count, char const format [], va_list arglist);  /*CPython*/
int __cdecl c99_vsnprintf_s (char *dst_buf, size_t size_in_bytes, size_t max_count, char const format [], va_list arglist);
int __cdecl c99_vswprintf (wchar_t *dst_buf, wchar_t const format [], va_list arglist);
int __cdecl c99_vswprintf_s (wchar_t *dst_buf, size_t size_in_words, wchar_t const format [], va_list arglist);
int __cdecl c99_vsnwprintf (wchar_t *dst_buf, size_t count, wchar_t const format [], va_list arglist);
int __cdecl c99_vsnwprintf_s (wchar_t *dst_buf, size_t size_in_words, size_t max_count, wchar_t const format [], va_list arglist);  /*CPython*/

int __cdecl c99_sprintf (char *dst_buf, char const format [], ...);  /*CPython*/
int __cdecl c99_sprintf_s (char *dst_buf, size_t size_in_bytes, char const format [], ...);  /*CPython*/
int __cdecl c99_snprintf (char *dst_buf, size_t count, char const format [], ...);  /*CPython*/
int __cdecl c99_snprintf_s (char *dst_buf, size_t size_in_bytes, size_t max_count, char const format [], ...);
int __cdecl c99_swprintf (wchar_t *dst_buf, wchar_t const format [], ...);
int __cdecl c99_swprintf_s (wchar_t *dst_buf, size_t size_in_words, wchar_t const format [], ...);
int __cdecl c99_snwprintf (wchar_t *dst_buf, size_t count, wchar_t const format [], ...);
int __cdecl c99_snwprintf_s (wchar_t *dst_buf, size_t size_in_words, size_t max_count, wchar_t const format [], ...);  /*CPython*/

/*===  v[f]printf() variants  ===*/
int __cdecl c99_vfprintf (FILE *file, char const format [], va_list arglist);  /*CPython*/
int __cdecl c99_vfprintf_s (FILE *file, char const format [], va_list arglist);
int __cdecl c99_vfwprintf (FILE *file, wchar_t const format [], va_list arglist);
int __cdecl c99_vfwprintf_s (FILE *file, wchar_t const format [], va_list arglist);  /*CPython*/
int __cdecl c99_vprintf (char const format [], va_list arglist);  /*CPython*/
int __cdecl c99_vwprintf (wchar_t const format [], va_list arglist);

/*===  [f]printf() variants  ===*/
int __cdecl c99_fprintf (FILE *file, char const format [], ...);  /*CPython*/
int __cdecl c99_fprintf_s (FILE *file, char const format [], ...);
int __cdecl c99_fwprintf (FILE *file, wchar_t const format [], ...);  /*CPython*/
int __cdecl c99_fwprintf_s (FILE *file, wchar_t const format [], ...);
int __cdecl c99_printf (char const format [], ...);  /*CPython*/
int __cdecl c99_wprintf (wchar_t const format [], ...);

/*===  [v]sscanf() variants  ===*/
int __cdecl c99_vsscanf (char const *src_buf, char const format [], va_list arglist);
int __cdecl c99_vswscanf (wchar_t const *src_buf, wchar_t const format [], va_list arglist);
int __cdecl c99_sscanf (char const *src_buf, char const format [], ...);  /*CPython*/
int __cdecl c99_swscanf (wchar_t const *src_buf, wchar_t const format [], ...);

/*===  v[f]scanf() variants  ===*/
int __cdecl c99_vfscanf (FILE *file, char const format [], va_list arglist);
int __cdecl c99_vfwscanf (FILE *file, wchar_t const format [], va_list arglist);
int __cdecl c99_vscanf (char const format [], va_list arglist);
int __cdecl c99_vwscanf (wchar_t const format [], va_list arglist);

/*===  [f]scanf() variants  ===*/
int __cdecl c99_fscanf (FILE *file, char const format [], ...);
int __cdecl c99_fwscanf (FILE *file, wchar_t const format [], ...);
int __cdecl c99_scanf (char const format [], ...);
int __cdecl c99_wscanf (wchar_t const format [], ...);

#ifdef __cplusplus
}
#endif

/* Map standard I/O functions to our wrappers: */
#ifndef BUILDING_C99COMPAT
#undef vsprintf
#define vsprintf        c99_vsprintf
#undef vsprintf_s
#define vsprintf_s      c99_vsprintf_s
#undef vsnprintf
#undef _vsnprintf
#define vsnprintf       c99_vsnprintf
#define _vsnprintf      c99_vsnprintf
#undef _vsnprintf_s
#define _vsnprintf_s    c99_vsnprintf_s

#undef vswprintf
#define vswprintf       c99_vswprintf
#undef _vswprintf_s
#define _vswprintf_s    c99_vswprintf_s
#undef vsnwprintf
#undef _vsnwprintf
#define vsnwprintf      c99_vsnwprintf
#define _vsnwprintf     c99_vsnwprintf
#undef _vsnwprintf_s
#define _vsnwprintf_s   c99_vsnwprintf_s

#undef sprintf
#define sprintf         c99_sprintf
#undef sprintf_s
#define sprintf_s       c99_sprintf_s
#undef snprintf
#undef _snprintf
#define snprintf        c99_snprintf
#define _snprintf       c99_snprintf
#undef _snprintf_s
#define _snprintf_s     c99_snprintf_s

#undef swprintf
#define swprintf        c99_swprintf
#undef swprintf_s
#define swprintf_s      c99_swprintf_s
#undef snwprintf
#undef _snwprintf
#define snwprintf       c99_snwprintf
#define _snwprintf      c99_snwprintf
#undef _snwprintf_s
#define _snwprintf_s    c99_snwprintf_s

#undef vfprintf
#define vfprintf        c99_vfprintf
#undef vfprintf_s
#define vfprintf_s      c99_vfprintf_s
#undef vfwprintf
#define vfwprintf       c99_vfwprintf
#undef vfwprintf_s
#define vfwprintf_s     c99_vfwprintf_s
#undef vprintf
#define vprintf         c99_vprintf
#undef vwprintf
#define vwprintf        c99_vwprintf

#undef fprintf
#define fprintf         c99_fprintf
#undef fprintf_s
#define fprintf_s       c99_fprintf_s
#undef fwprintf
#define fwprintf        c99_fwprintf
#undef fwprintf_s
#define fwprintf_s      c99_fwprintf_s
#undef printf
#define printf          c99_printf
#undef wprintf
#define wprintf         c99_wprintf

#undef vsscanf
#define vsscanf         c99_vsscanf
#undef vswscanf
#define vswscanf        c99_vswscanf
#undef sscanf
#define sscanf          c99_sscanf
#undef swscanf
#define swscanf         c99_swscanf

#undef vfscanf
#define vfscanf         c99_vfscanf
#undef vfwscanf
#define vfwscanf        c99_vfwscanf
#undef vscanf
#define vscanf          c99_vscanf
#undef vwscanf
#define vwscanf         c99_vwscanf

#undef fscanf
#define fscanf          c99_fscanf
#undef fwscanf
#define fwscanf         c99_fwscanf
#undef scanf
#define scanf           c99_scanf
#undef wscanf
#define wscanf          c99_wscanf
#endif

#endif
