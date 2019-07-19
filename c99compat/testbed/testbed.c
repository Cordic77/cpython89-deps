#include <c/stdinc.h>

#include <crtdbg.h>
#include <time.h>

#include "c99fmtio.h"


static BOOL test_printf (void);
static BOOL test_wprintf (void);

static BOOL test_sscanf (void);
static BOOL test_wsscanf (void);


int main (void)
{
  srand ((unsigned int)time (NULL));

  fprintf (stderr, "Testing \"v99compat\" printf() functions:");
  fprintf (stderr, "\n==============================================================================\n");
  test_printf ();
  fprintf (stderr, "\n==============================================================================\n");
  test_printf ();
  fprintf (stderr, "\n==============================================================================\n");
  test_sscanf ();
  fprintf (stderr, "\n==============================================================================\n");
  test_wsscanf ();
  fprintf (stderr, "\n==============================================================================\n");

  return (0);
}


//
// Test C99's additional argument length/size modifiers:
//
static BOOL test_printf (void)
{ signed char c = -127;
  signed short h = -32767;
  size_t z = (size_t)-1;
  intmax_t j = (intmax_t)(z / 2);

  fprintf (stdout, "%4.3hhd, %6hu, %-15jd, %+10zu\nshould produce:\n-127, -32767, 2147483647     , 4294967295\n", c, h, j, z);

  return (TRUE);
}


static BOOL test_wprintf (void)
{ signed char c = -127;
  signed short h = -32767;
  size_t z = (size_t)-1;
  intmax_t j = (intmax_t)(z / 2);

  fwprintf (stdout, L"%4.3hhd, %6hu, %-15jd, %+10zu\nshould produce:\n-127, -32767, 2147483647     , 4294967295\n", c, h, j, z);

  return (TRUE);
}


static BOOL test_sscanf (void)
{ char const *str_data = "-127, 32769, 2147483647, 4294967295\n";
  signed char c;
  signed short h;
  size_t z;
  intmax_t j;

  fprintf (stderr, "scanf (\"%%hhd, %%hu, %%jd, %%zu\") ... ");
  sscanf (str_data, "%hhd, %hu, %jd, %zu", &c, &h, &j, &z);

  assert (c == -127);
  assert (h == -32767);
  assert (z == 4294967295);
  assert (j == 2147483647);
  fprintf (stderr, "OK");
  return (TRUE);
}


static BOOL test_wsscanf (void)
{ wchar_t const *str_data = L"-127, 32769, 2147483647, 4294967295\n";
  signed char c;
  signed short h;
  size_t z;
  intmax_t j;

  fwprintf (stderr, L"scanf (\"%%hhd, %%hu, %%jd, %%zu\") ... ");
  swscanf (str_data, L"%hhd, %hu, %jd, %zu", &c, &h, &j, &z);

  assert (c == -127);
  assert (h == -32767);
  assert (z == 4294967295);
  assert (j == 2147483647);
  fwprintf (stderr, L"OK");
  return (TRUE);
}
