/***************************************************************************

  Author: Michael Stumpfl

  Date:   2019-07-15

  API:    C

  Libraries:
    ---

  Functionality:
    ISO/IEC 9899:1999 compatibility macros, functions and types.

  Known Bugs:
    ---

****************************************************************************/
#include "c99fmtio.h"

/*stdio.h:528
  #define _SWPRINTFS_DEPRECATED _CRT_DEPRECATE_TEXT("swprintf has been changed to conform with the ISO C standard, adding an extra character count parameter. To use traditional Microsoft swprintf, set _CRT_NON_CONFORMING_SWPRINTFS.")
*/
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <stdio.h>                /* vprintf() */
#include <stdlib.h>               /* malloc() */
#include <string.h>               /* memcpy(), strchr() */
#include <stdarg.h>               /* va_list, va_start(), va_arg(), va_end() */


#if defined(__cplusplus)
  #ifndef EXTERN_C
  #define EXTERN_C extern "C"
  #endif
#else
  #ifndef EXTERN_C
  #define EXTERN_C extern
  #endif
#endif


/*
// As stated by the Microsoft documentation,
// "The hh, j, z, and t length prefixes are not supported."
*/
static char const *c89_compatible_fmtstr (char const format [])
{ char *
    c89format = NULL;             /* A newly allocated, C89 compatible format string (if necessary) */
  int
    modify_arglen = 0;            /* Replace (with back compatible) argument length/size modifier? */

  /* https://docs.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions
     A conversion specification consists of optional and required fields in this form:

     %[flags][width][.precision][size]type

     flags     = [-+0 #]
     width     = (\d*|\*)
     precision = (\d*|\*)
     size      = (hh|h|l|ll|j|z|t|L)
     type      = [diuoxXfFeEgGaAcspn]
  */
  char const *cur = format - 1;
  char *dst = NULL;

  char const *fragment_start = cur + 1;

  while ((cur=strchr (cur + 1, '%')) != NULL)
  {
    modify_arglen = 0;

    /* skip (optional) width and precision fields: */
    while (*++cur != '\0' && strchr ("-+0 #0123456789.*", *cur) != NULL)
      ;

      /*      %hh = (un)signed char       %j = u?intmax_t  %z = s?size_t  %t = ptrdiff_t */
    if (((*cur == 'h' && *++cur == 'h') || *cur == 'j' || *cur == 'z' || *cur == 't')
        && strchr("diuoxX", *(cur+1)) != NULL /* matching type character? */)
      modify_arglen = 1;

    if (modify_arglen)
    {
      /* Request a newly allocated 'c89format' string from the heap? */
      if (c89format == NULL)
      {
        /* A format string consisting only of %jd or %ju could grow by 50% in the worst case: */
        c89format = (char *)malloc ((strlen (format) * 3) >> 1);
        dst = c89format;
      }

      /* Replace argument length/size modifier: */
      { size_t length = cur - fragment_start;

        memcpy (dst, fragment_start, length);
        dst += length;

        /* Try to order these by expected frequency: */
        if (*cur == 'z')
         *dst++ = 'I';    /* the correct prefix to use for size_t is I -- so you'd use %Iu */
        else
        if (*cur == 'j' || *cur == 't')
        {
         *dst++ = 'l';    /* print (u)intmax_t and ptrdiff_t by specifying ll (long long) */
         *dst++ = 'l';
        }
        else
        if (*cur == 'h')
          --dst;          /* are passed as 'int' by a C89-compatible compiler! */

       *dst++ = *(cur+1);
       *dst = '\0';
      }

      fragment_start = cur + 2;
    }
  }

  if (c89format == NULL)
    return (format);

  strcat (c89format, fragment_start);
  return (c89format);
}


static wchar_t const *c89_compatible_fmtwcs (wchar_t const format [])
{ wchar_t *
    c89format = NULL;             /* A newly allocated, C89 compatible format string (if necessary) */
  int
    modify_arglen = 0;            /* Replace (with back compatible) argument length/size modifier? */

  /* https://docs.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions
     A conversion specification consists of optional and required fields in this form:

     %[flags][width][.precision][size]type

     flags     = [-+0 #]
     width     = (\d*|\*)
     precision = (\d*|\*)
     size      = (hh|h|l|ll|j|z|t|L)
     type      = [diuoxXfFeEgGaAcspn]
  */
  wchar_t const *cur = format - 1;
  wchar_t *dst = NULL;

  wchar_t const *fragment_start = cur + 1;

  while ((cur=wcschr (cur + 1, L'%')) != NULL)
  {
    modify_arglen = 0;

    /* skip (optional) width and precision fields: */
    while (*++cur != L'\0' && wcschr (L"-+0 #0123456789.*", *cur) != NULL)
      ;

      /*       %hh = (un)signed char       %j = u?intmax_t  %z = s?size_t  %t = ptrdiff_t */
    if (((*cur == L'h' && *++cur == L'h') || *cur == L'j' || *cur == L'z' || *cur == L't')
        && strchr("diuoxX", *(cur+1)) != NULL /* matching type character? */)
      modify_arglen = 1;

    if (modify_arglen)
    {
      /* Request a newly allocated 'c89format' string from the heap? */
      if (c89format == NULL)
      {
        /* A format string consisting only of %jd or %ju could grow by 50% in the worst case: */
        c89format = (wchar_t *)malloc (wcslen (format) * 3);
        dst = c89format;
      }

      /* Replace argument length/size modifier: */
      { size_t length = cur - fragment_start;

        memcpy (dst, fragment_start, length*sizeof(wchar_t));
        dst += length;

        /* Try to order these by expected frequency: */
        if (*cur == L'z')
         *dst++ = L'I';    /* the correct prefix to use for size_t is I -- so you'd use %Iu */
        else
        if (*cur == L'j' || *cur == L't')
        {
         *dst++ = L'l';    /* print (u)intmax_t and ptrdiff_t by specifying ll (long long) */
         *dst++ = L'l';
        }
        else
        if (*cur == L'h')
          --dst;          /* are passed as 'int' by a C89-compatible compiler! */

       *dst++ = *(cur+1);
       *dst = L'\0';
      }

      fragment_start = cur + 2;
    }
  }

  if (c89format == NULL)
    return (format);

  wcscat (c89format, fragment_start);
  return (c89format);
}


/*
// Formatted I/O wrapper functions:
*/

/*===  [v]sprintf() variants  ===*/
int __cdecl c99_vsprintf (char *dst_buf, char const format [], va_list arglist)
{ int
    retval;
  char const *
    c89format = c89_compatible_fmtstr (format);

  retval = vsprintf (dst_buf, c89format, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vsprintf_s (char *dst_buf, size_t size_in_bytes, char const format [], va_list arglist)
{ int
    retval;
  char const *
    c89format = c89_compatible_fmtstr (format);

  retval = vsprintf_s (dst_buf, size_in_bytes, c89format, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vsnprintf (char *dst_buf, size_t count, char const format [], va_list arglist)
{ int
    retval;
  char const *
    c89format = c89_compatible_fmtstr (format);

  retval = _vsnprintf (dst_buf, count, c89format, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vsnprintf_s (char *dst_buf, size_t size_in_bytes, size_t max_count, char const format [], va_list arglist)
{ int
    retval;
  char const *
    c89format = c89_compatible_fmtstr (format);

  retval = _vsnprintf_s (dst_buf, size_in_bytes, max_count, c89format, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vswprintf (wchar_t *dst_buf, wchar_t const format [], va_list arglist)
{ int
    retval;
  wchar_t const *
    c89format = c89_compatible_fmtwcs (format);

  retval = _vswprintf (dst_buf, c89format, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vswprintf_s (wchar_t *dst_buf, size_t size_in_words, wchar_t const format [], va_list arglist)
{ int
    retval;
  wchar_t const *
    c89format = c89_compatible_fmtwcs (format);

  retval = vswprintf_s (dst_buf, size_in_words, c89format, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vsnwprintf (wchar_t *dst_buf, size_t count, wchar_t const format [], va_list arglist)
{ int
    retval;
  wchar_t const *
    c89format = c89_compatible_fmtwcs (format);

  retval = _vsnwprintf (dst_buf, count, c89format, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vsnwprintf_s (wchar_t *dst_buf, size_t size_in_words, size_t max_count, wchar_t const format [], va_list arglist)
{ int
    retval;
  wchar_t const *
    c89format = c89_compatible_fmtwcs (format);

  retval = _vsnwprintf_s (dst_buf, size_in_words, max_count, c89format, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_sprintf (char *dst_buf, char const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vsprintf (dst_buf, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_sprintf_s (char *dst_buf, size_t size_in_bytes, char const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vsprintf_s (dst_buf, size_in_bytes, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_snprintf (char *dst_buf, size_t count, char const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vsnprintf (dst_buf, count, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_snprintf_s (char *dst_buf, size_t size_in_bytes, size_t max_count, char const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vsnprintf_s (dst_buf, size_in_bytes, max_count, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_swprintf (wchar_t *dst_buf, wchar_t const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vswprintf (dst_buf, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_swprintf_s (wchar_t *dst_buf, size_t size_in_words, wchar_t const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vswprintf_s (dst_buf, size_in_words, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_snwprintf (wchar_t *dst_buf, size_t count, wchar_t const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vsnwprintf (dst_buf, count, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_snwprintf_s (wchar_t *dst_buf, size_t size_in_words, size_t max_count, wchar_t const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vsnwprintf_s (dst_buf, size_in_words, max_count, format, arglist);
  va_end (arglist);

  return (retval);
}


/*===  v[f]printf() variants  ===*/
int __cdecl c99_vfprintf (FILE *file, char const format [], va_list arglist)
{ int
    retval;
  char const *
    c89format = c89_compatible_fmtstr (format);

  retval = vfprintf (file, c89format, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vfprintf_s (FILE *file, char const format [], va_list arglist)
{ int
    retval;
  char const *
    c89format = c89_compatible_fmtstr (format);

  retval = vfprintf_s (file, c89format, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vfwprintf (FILE *file, wchar_t const format [], va_list arglist)
{ int
    retval;
  wchar_t const *
    c89format = c89_compatible_fmtwcs (format);

  retval = vfwprintf (file, c89format, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vfwprintf_s (FILE *file, wchar_t const format [], va_list arglist)
{ int
    retval;
  wchar_t const *
    c89format = c89_compatible_fmtwcs (format);

  retval = vfwprintf_s (file, c89format, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vprintf (char const format [], va_list arglist)
{
  return (c99_vfprintf (stdout, format, arglist));
}


int __cdecl c99_vwprintf (wchar_t const format [], va_list arglist)
{
  return (c99_vfwprintf (stdout, format, arglist));
}


/*===  [f]printf() variants  ===*/
int __cdecl c99_fprintf (FILE *file, char const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vfprintf (file, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_fprintf_s (FILE *file, char const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vfprintf_s (file, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_fwprintf (FILE *file, wchar_t const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vfwprintf (file, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_fwprintf_s (FILE *file, wchar_t const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vfwprintf_s (file, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_printf (char const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vfprintf (stdout, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_wprintf (wchar_t const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vfwprintf (stdout, format, arglist);
  va_end (arglist);

  return (retval);
}


/* VS2008 vscanf alternative? http://social.msdn.microsoft.com/forums/en-US/vclanguage/thread/b043efbc-b4d8-413b-bd21-937bd0d5dd8e/ */
#ifdef _SAFECRT_IMPL
  EXTERN_C int __cdecl crt_input_s (FILE *stream, char const format [], va_list arglist);
  #define crt_input(file, format, locale, arglist) crt_input_s(file, format, arglist)

  EXTERN_C int __cdecl crt_winput_s (FILE *stream, wchar_t const format [], va_list arglist);
  #define crt_winput(file, format, locale, arglist) crt_winput_s(file, format, arglist)
#else
  EXTERN_C int __cdecl crt_input_l (FILE *file, char const format [], _locale_t locale, va_list arglist);
  #define crt_input crt_input_l

  EXTERN_C int __cdecl crt_winput_l (FILE *file, wchar_t const format [], _locale_t locale, va_list arglist);
  #define crt_winput crt_winput_l
#endif


/*===  [v]sscanf() variants  ===*/
int __cdecl c99_vsscanf (char const *src_buf, char const format [], va_list arglist)
{ int
    retval;
  char const *
    c89format = c89_compatible_fmtstr (format);
  FILE
    str;

  str._flag = _IOREAD | _IOSTRG | _IOMYBUF;
  str._ptr = str._base = (char *)src_buf;
  str._cnt = INT_MAX;  /* strlen(src_buf)+1;  // (?) On the other hand, 'src_buf' needn't be null-terminated! */
  retval = crt_input (&str, c89format, NULL, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vswscanf (wchar_t const *src_buf, wchar_t const format [], va_list arglist)
{ int
    retval;
  wchar_t const *
    c89format = c89_compatible_fmtwcs (format);
  FILE
    str;

  str._flag = _IOREAD | _IOSTRG | _IOMYBUF;
  str._ptr = str._base = (char *)src_buf;
  str._cnt = INT_MAX;  /* (strlen(src_buf)+1)*sizeof(wchar_t);  // (?) On the other hand, 'src_buf' needn't be null-terminated! */
  retval = crt_winput (&str, c89format, NULL, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_sscanf (char const *src_buf, char const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vsscanf (src_buf, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_swscanf (wchar_t const *src_buf, wchar_t const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vswscanf (src_buf, format, arglist);
  va_end (arglist);

  return (retval);
}


/*===  v[f]scanf() variants  ===*/
int __cdecl c99_vfscanf (FILE *file, char const format [], va_list arglist)
{ int
    retval;
  char const *
    c89format = c89_compatible_fmtstr (format);

  retval = crt_input (file, c89format, NULL, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vfwscanf (FILE *file, wchar_t const format [], va_list arglist)
{ int
    retval;
  wchar_t const *
    c89format = c89_compatible_fmtwcs (format);

  retval = crt_winput (file, c89format, NULL, arglist);

  if (c89format != format)
    free ((void *)c89format);

  return (retval);
}


int __cdecl c99_vscanf (char const format [], va_list arglist)
{
  return (c99_vfscanf (stdin, format, arglist));
}


int __cdecl c99_vwscanf (wchar_t const format [], va_list arglist)
{
  return (c99_vfwscanf (stdin, format, arglist));
}


/*===  [f]scanf() variants  ===*/
int __cdecl c99_fscanf (FILE *file, char const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = crt_input (file, format, NULL, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_fwscanf (FILE *file, wchar_t const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = crt_winput (file, format, NULL, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_scanf (char const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vfscanf (stdin, format, arglist);
  va_end (arglist);

  return (retval);
}


int __cdecl c99_wscanf (wchar_t const format [], ...)
{ va_list arglist;
  int retval;

  va_start (arglist, format);
  retval = c99_vfwscanf (stdin, format, arglist);
  va_end (arglist);

  return (retval);
}
